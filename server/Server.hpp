#pragma once

#include <Nuts/Networking.hpp>

#include <vector>
#include <iostream>
#include <stdio.h>

#include "SClientManager.hpp"

class Server
{
    private:
        std::unique_ptr<SClientManager> _clientManager;

        sf::TcpListener _listener;
        sf::TcpSocket _tmpTcpSock;
        bool isRunning = false;

    public:
        void Init() {
            _clientManager = std::make_unique<SClientManager>();
        }

        void Listen(std::uint16_t port)
        {
            _listener.setBlocking(false);
            _listener.listen(port);

            std::cout << "Server listening on port:["
                    << port << "]\n";

            isRunning = true;
        };

        sf::Socket::Status Accept()
        {
            sf::Socket::Status status = _listener.accept(_tmpTcpSock);

            if (status == sf::Socket::Done)
            {
                _clientManager->PushClient(_tmpTcpSock);
            }

            return status;
        };

        void Dispatch()
        {
            for (sf::TcpSocket *clientSocket : _clientManager->_clientSockets)
            {
                sf::Packet remotePacket;
                Rpc rpcType = -1;

                sf::Socket::Status status = clientSocket->receive(remotePacket);
                if (status == sf::Socket::Done)
                {
                    remotePacket >> rpcType;
                    switch (rpcType)
                    {
                    case ERpc::CLIENT_CONNECT:
                    {
                        printf("new connection request from IP:[%s] | PORT:[%d]\n", clientSocket->getRemoteAddress().toString().c_str(), clientSocket->getRemotePort());
                        _clientManager->RegisterClient(clientSocket);

                        break;
                    }
                    case ERpc::CLIENT_DISCONNECT:
                    {
                        ClientID remoteId;
                        remotePacket >> remoteId;
                        printf("client [%d] disconnected\n", remoteId);

                        break;
                    }
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

        void ShutDown(){};
};
