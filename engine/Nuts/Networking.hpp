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

#if !defined(HASH)
// static const std::hash<char *> strHasher; // TODO: <char *> but <std::string> produces one hash
// #define HASH(x) (strHasher("x"))
#endif

namespace Net {

    enum Events
    {
        CLIENT_CONNECT = 1000,
        CLIENT_DISCONNECT,
        CLIENT_ID,
        CLIENTS_PRINT,

        UDP_INFO,
        UDP_OK,

        LOBBY_LOAD,
        LOBBY_LIST,
        LOBBY_CREATE,
        LOBBY_JOIN,
        LOBBY_CLIENTS,
        LOBBY_QUIT,
        LOBBY_READY,
        LOBBY_READY_OK,
        LOBBY_CANCEL,
        LOBBY_CANCEL_OK,
    };

    class INetClient
    {
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
