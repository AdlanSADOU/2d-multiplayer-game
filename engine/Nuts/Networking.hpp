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

#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <memory>
#include <string>

#include "EcsCore/Event.hpp"

using ClientID = std::int32_t;

namespace Net {

    namespace Events {
        const EventType CLIENT_CONNECT    = HASH(Events::CLIENT_CONNECT);
        const EventType CLIENT_DISCONNECT = HASH(Events::CLIENT_DISCONNECT);
        const EventType CLIENT_ID         = HASH(Events::CLIENT_ID);
        const EventType CLIENTS_PRINT     = HASH(Events::CLIENTS_PRINT);
        const EventType UDP_INFO          = HASH(Events::UDP_INFO);
        const EventType UDP_OK            = HASH(Events::UDP_OK);
        const EventType LOBBY_LOAD        = HASH(Events::LOBBY_LOAD);
        const EventType LOBBY_LIST        = HASH(Events::LOBBY_LIST);
        const EventType LOBBY_CREATE      = HASH(Events::LOBBY_CREATE);
        const EventType LOBBY_JOIN        = HASH(Events::LOBBY_JOIN);
        const EventType LOBBY_CLIENTS     = HASH(Events::LOBBY_CLIENTS);
        const EventType LOBBY_QUIT        = HASH(Events::LOBBY_QUIT);
        const EventType LOBBY_READY       = HASH(Events::LOBBY_READY);
        const EventType LOBBY_READY_OK    = HASH(Events::LOBBY_READY_OK);
        const EventType LOBBY_CANCEL      = HASH(Events::LOBBY_CANCEL);
        const EventType LOBBY_CANCEL_OK   = HASH(Events::LOBBY_CANCEL_OK);
    }

    class INetClient {
    private:
        sf::TcpSocket _tcpSocket;
        sf::UdpSocket _udpSocket;

        sf::IpAddress _remoteGameIp;
        std::uint16_t _remoteGamePort;

        ClientID _clientId    = -1;
        bool     _isConnected = false;

        void TcpReceive()
        {
            sf::Packet packet;

            if (_tcpSocket.receive(packet) == sf::Socket::Done) {
                EventType type;
                packet >> type;
                std::cout << "[Net]: received TCP EventType:" << type << "\n";

                Event event(type);
                event.SetParam<sf::Packet>(0, packet);
                scene.InvokeEvent(event);
            }
        }

        void UdpReceive()
        {
            sf::Packet packet {};
            EventType  type {};
            packet >> type;

            if (_udpSocket.receive(packet, _remoteGameIp, _remoteGamePort) == sf::Socket::Done) {
                std::cout << "[Net]: received UDP " << packet << "\n";
            }
        }

    public:
        INetClient() {};

        ~INetClient()
        {
            _tcpSocket.disconnect();
        }

        void Update()
        {
            this->TcpReceive();
            this->UdpReceive();
        }

        bool Connect(sf::IpAddress serverIp, int serverPort)
        {
            if (_tcpSocket.connect(serverIp, static_cast<std::uint16_t>(serverPort)) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to connect to ["
                          << serverIp << ":"
                          << serverPort << "]\n";
                return false;
            }

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

        void SetLocalClientId(ClientID id)
        {
            _clientId = id;
        }

        ClientID GetLocalClientId() const
        {
            return _clientId;
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
            if (!_isConnected) return;

            if (_udpSocket.send(packet, _remoteGameIp, _remoteGamePort) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to send TCP packet\n";
            }
        }

        void SetRemoteUdpEndpoint(sf::IpAddress &serverIp, std::uint16_t serverPort)
        {
            _remoteGameIp   = serverIp;
            _remoteGamePort = serverPort;
        }
    };

}
