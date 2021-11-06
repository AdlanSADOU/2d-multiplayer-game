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

#include "Dispatcher.hpp"
#include "Lobby.hpp"
#include "SClientManager.hpp"

typedef void (*RemoteCallPtr)(sf::Packet& packet);
std::unique_ptr<SClientManager> _clientManager;

class Server {
private:
    std::unique_ptr<Dispatcher> _dispatcher;

    sf::TcpListener _listener;
    sf::UdpSocket _udpSock;
    sf::TcpSocket* sockPtr = nullptr;

    bool isRunning = false;

public:
    void Init()
    {
        _clientManager = std::make_unique<SClientManager>();
        _dispatcher = std::make_unique<Dispatcher>();

        _dispatcher->Init();
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

    void Receive()
    {
        for (auto& client : _clientManager->clients) {
            sf::Packet remotePacket;
            if (!client.second.tcp) {
                printf("[ERROR]: client socket with ID:[%d] is nullptr\n", client.second.uuid);
                return;
            }

            sf::Socket::Status status = client.second.tcp->receive(remotePacket);
            if (status == sf::Socket::Done) {

                printf("[SERVER_TCP]: received Rpc\n");
                if (_dispatcher->Dispatch(remotePacket))
                    return;
            }
        }

        {
            sf::Packet remotePacket;
            Rpc rpcType = -1;

            sf::IpAddress remoteAddress;
            unsigned short remotePort;

            sf::Socket::Status status = _udpSock.receive(remotePacket, remoteAddress, remotePort);
            if (status == sf::Socket::Done) {

                printf("[SERVER_UDP]: received Rpc\n");
                _dispatcher->Dispatch(remotePacket);
            }
        }
    };

    bool IsRunning() const
    {
        return isRunning;
    };

    void ShutDown() {};
};
