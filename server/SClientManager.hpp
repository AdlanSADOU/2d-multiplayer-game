#pragma once

#include "SClient.hpp"
#include <unordered_map>

class SClientManager {
private:
    ClientID _clientId = 0;

public:
    std::vector<SClient> clients {};
    // std::vector<sf::TcpSocket*> clientSockets {};
    SClient& GetClientById() {

    };

    // void PushClientSocket(sf::TcpSocket& newTcpClient)
    // {
    //     sf::TcpSocket* tcpSockPtr = new sf::TcpSocket();
    //     tcpSockPtr = &newTcpClient;

    //     printf("incomming connection\n");
    //     tcpSockPtr->setBlocking(false);
    //     clientSockets.push_back(tcpSockPtr);
    // };

    void RegisterClient(sf::TcpSocket* socket)
    {
        bool isRegistered = false;
        printf("new request from [%s:%d]\n\n",
            socket->getRemoteAddress().toString().c_str(), socket->getRemotePort());

        for (auto const& client : clients) {
            if (client.socket && socket->getRemoteAddress() == client.socket->getRemoteAddress() && socket->getRemotePort() == client.socket->getRemotePort()) {
                printf("client already connected as ");
                printf("ID:[%d] from [%s:%d] | sockPtr:[%p]\n\n",
                    client.uuid, client.socket->getRemoteAddress().toString().c_str(), client.socket->getRemotePort(), client.socket);
                isRegistered = true;
                break;
            }
        }

        if (isRegistered)
            return;

        SClient tmpClient;
        tmpClient.socket = socket;
        tmpClient.connected = true;
        tmpClient.IsInLobby = false;
        tmpClient.uuid = _clientId;
        clients.push_back(tmpClient);

        sf::Packet idPacket;
        idPacket << static_cast<sf::Uint8>(ERpc::CLIENT_CONNECT) << tmpClient.uuid;

        sf::Socket::Status status;
        if ((status = socket->send(idPacket)) != sf::Socket::Done)
            printf("[SERVER]:CLIENT_CONNECT::Error: Status:[%d]", status);

        printf("[SERVER]: Client connected as ID:[%d] from [%s:%d]\n\n",
            _clientId, socket->getRemoteAddress().toString().c_str(), tmpClient.socket->getRemotePort());

        ++_clientId;
    };

    void PrintConnectedClients()
    {
        printf("[SERVER]: Connected clients:\n");
        for (auto const& client : clients) {
            printf("------ ID:[%d] from [%s:%d] | sockPtr:[%p]\n",
                client.uuid, client.socket->getRemoteAddress().toString().c_str(), client.socket->getRemotePort(), client.socket);
        }
    }
};
