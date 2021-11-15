/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#if defined(_WIN32)
#pragma warning(disable : 4091)
#endif //_WIN32

#define NET_LOG 1

#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <memory>
#include <string>

#include "EcsCore/Event.hpp"

using ClientID = sf::Int32;

namespace Net {

    namespace Events {
        const EventType CLIENT_CONNECT    = HASH(Events::CLIENT_CONNECT);
        const EventType CLIENT_DISCONNECT = HASH(Events::CLIENT_DISCONNECT);
        const EventType CLIENT_QUIT       = HASH(Events::CLIENT_QUIT);
        const EventType CLIENT_ID         = HASH(Events::CLIENT_ID);
        const EventType CLIENTS_PRINT     = HASH(Events::CLIENTS_PRINT);
        const EventType CLIENT_UDP        = HASH(Events::CLIENT_UDP);
        const EventType NEW_CLIENT        = HASH(Events::NEW_CLIENT);
        const EventType UDP_OK            = HASH(Events::UDP_OK);
        const EventType MATCHM_INIT       = HASH(Events::MATCHM_INIT);
        const EventType MATCHM_OK         = HASH(Events::MATCHM_OK);
        const EventType MATCHM_PLAY       = HASH(Events::MATCHM_PLAY);
        const EventType GAMEID            = HASH(Events::GAMEID);
        const EventType GAMEID_OK         = HASH(Events::GAMEID_OK);
        const EventType INITIAL_GAME_INFO = HASH(Events::INITIAL_GAME_INFO);
    }

    class INetClient {
    private:
        sf::TcpSocket _tcpSocket;
        sf::UdpSocket _udpSocket;

        sf::IpAddress  _remoteGameIp;
        sf::Uint16 _remoteGameUdpPort;

        sf::IpAddress  _remoteServerIp;
        sf::Uint16 _remoteServerPort;

        ClientID _clientId    = -1;
        bool     _isConnected = false;

        void TcpReceive()
        {
            sf::Packet packet;

            if (_tcpSocket.receive(packet) == sf::Socket::Done) {
                EventType type;
                packet >> type;

                Event event(type);
                event.SetParam<sf::Packet>(0, packet);
                scene.InvokeEvent(event);

#if defined(NET_LOG)
                std::cout << "[Net]: received TCP EventType:" << type << "\n";
#endif // NET_LOG
            }
        }

        void UdpReceive()
        {
            sf::Packet packet {};

            if (_udpSocket.receive(packet, _remoteServerIp, _remoteGameUdpPort) == sf::Socket::Done) {
                EventType type {};
                packet >> type;

                Event event(type);
                event.SetParam<sf::Packet>(0, packet);
                scene.InvokeEvent(event);

#if defined(NET_LOG)
                std::cout << "[Net]: received UDP " << packet << "\n";
#endif // NET_LOG
            }
        }

    public:
        INetClient() {};

        ~INetClient()
        {
            _tcpSocket.disconnect();
        }

        ClientID GetLocalClientId() const
        {
            return _clientId;
        }

        sf::Uint16 GetLocalUdpPort() const
        {
            return _udpSocket.getLocalPort();
        }

        sf::IpAddress GetRemoteServerIp() const
        {
            return _remoteServerIp;
        }

        sf::Uint16 GetRemoteServerPort() const
        {
            return _remoteServerPort;
        }

        bool IsConnected() const
        {
            return _isConnected;
        }

        void SetLocalClientId(ClientID id)
        {
            _clientId = id;
        }

        void Update()
        {
            this->TcpReceive();
            this->UdpReceive();
        }

        bool Connect(sf::IpAddress serverIp, sf::Uint16 serverPort)
        {
            if (_tcpSocket.connect(serverIp, serverPort) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to connect to ["
                          << serverIp << ":"
                          << serverPort << "]\n";
                return false;
            }

            _remoteServerIp    = serverIp;
            _remoteServerPort  = serverPort;
            _remoteGameIp      = serverIp;
            _remoteGameUdpPort = serverPort + 1;

            if (_udpSocket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress()) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to connect to ["
                          << serverIp << ":"
                          << serverPort << "]\n";
                return false;
            }

            _tcpSocket.setBlocking(false);
            _udpSocket.setBlocking(false);
            _isConnected = true;

            std::cout << "[Net]: Connected to ["
                      << serverIp << ":"
                      << serverPort << "]\n";

            return true;
        }

        void Disconnect()
        {
            if (_isConnected)
                _tcpSocket.disconnect();
        }

        void TcpSend(sf::Packet &packet)
        {
            if (!_isConnected) return;

            if (_tcpSocket.send(packet) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to send TCP packet\n";
            }
        }

        void UdpSend(sf::Packet &packet)
        {
            // if (!_isConnected) return;

            if (_udpSocket.send(packet, _remoteGameIp, _remoteGameUdpPort) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to send TCP packet\n";
            }
        }

        void SetRemoteGameUdpEndpoint(sf::IpAddress &gameIp, sf::Uint16 gamePort)
        {
            _remoteGameIp      = gameIp;
            _remoteGameUdpPort = gamePort;
        }
    };
}
