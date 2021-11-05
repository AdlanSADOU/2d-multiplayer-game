/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Server.hpp
*/

#pragma once

#include <Nuts/Networking.hpp>

#include <iostream>
#include <stdio.h>
#include <vector>

#include "Lobby.hpp"
#include "SClientManager.hpp"

class Server {
private:
    std::unique_ptr<SClientManager> _clientManager;

    sf::TcpListener _listener;
    sf::UdpSocket _udpSock;
    bool isRunning = false;
    sf::TcpSocket* sockPtr = nullptr;

public:
    void Init()
    {
        _clientManager = std::make_unique<SClientManager>();
    }

    void Listen(std::uint16_t port)
    {
        _listener.setBlocking(false);
        _listener.listen(port);

        _udpSock.bind(port + 1, sf::IpAddress::LocalHost);
        _udpSock.setBlocking(false);

        sockPtr = new sf::TcpSocket();
        std::cout << "Server listening on port:[" << port << "]\n\n";

        isRunning = true;
    };

    sf::Socket::Status Accept()
    {
        sf::Socket::Status status = _listener.accept(*sockPtr);

        if (status == sf::Socket::Done) {
            sockPtr->setBlocking(false);
            _clientManager->RegisterClient(sockPtr);
            sockPtr = new sf::TcpSocket();
        } else if (status == sf::Socket::Error)
            printf("accept error\n");
        else if (status == sf::Socket::Partial)
            printf("accept Partial\n");

        return status;
    };

    void Dispatch()
    {
        for (auto& client : _clientManager->clients) {
            sf::Packet remotePacket;
            Rpc rpcType = -1;

            if (!client.second.tcp) {
                printf("[ERROR]: client socket with ID:[%d] is nullptr\n", client.second.uuid);
                continue;
            }

            assert(client.second.tcp && "socket is nullptr");

            sf::Socket::Status status = client.second.tcp->receive(remotePacket);
            if (status == sf::Socket::Done) {
                remotePacket >> rpcType;

                printf("[SERVER]: received Rpc type:[%d]\n", rpcType);

                switch (rpcType) {

                case ERpc::CLIENT_DISCONNECT: {
                    ClientID remoteId;
                    remotePacket >> remoteId;
                    if (_clientManager->DisconnectClient(remoteId))
                        return;
                } break;

                case ERpc::CLIENTS_PRINT: {
                    _clientManager->PrintConnectedClients();
                } break;

                default:
                    break;
                }
            }
        }

        {
            sf::Packet remotePacket;
            Rpc rpcType = -1;

            sf::IpAddress remoteAddress;
            unsigned short remotePort;

            ClientID clientId;

            sf::Socket::Status status = _udpSock.receive(remotePacket, remoteAddress, remotePort);
            if (status == sf::Socket::Done) {
                remotePacket >> rpcType >> clientId;

                printf("[SERVER]: received Rpc type:[%d] from ID:[%d]:[%s:%d]\n", rpcType, clientId, remoteAddress.toString().c_str(), remotePort);

                switch (rpcType) {

                case ERpc::CLIENT_CONNECT: {
                    ClientID remoteId;
                    remotePacket >> remoteId;
                    if (_clientManager->DisconnectClient(remoteId))
                        return;
                } break;

                case ERpc::CLIENTS_PRINT: {
                    _clientManager->PrintConnectedClients();
                } break;

                default:
                    break;
                }
            }
        }
    };

    bool IsRunning() const
    {
        return isRunning;
    };

    void ShutDown() {};
};
