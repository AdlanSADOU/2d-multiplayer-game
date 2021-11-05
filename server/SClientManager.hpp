#pragma once

#include "SClient.hpp"
#include <unordered_map>

class SClientManager {
private:
    ClientID _clientId = 0;

public:
    /** TODO(adlan):
    * we might want to change this into an unordered_map<ClientId, SClient>
    * to be able to .find
    */
    std::unordered_map<ClientID, SClient> clients {};
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
        if (socket == nullptr) return;

        SClient tmpClient;
        tmpClient.socket = socket;
        tmpClient.connected = true;
        tmpClient.IsInLobby = false;
        tmpClient.uuid = _clientId;
        clients.insert({_clientId, tmpClient});

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
                client.second.uuid, client.second.socket->getRemoteAddress().toString().c_str(), client.second.socket->getRemotePort(), client.second.socket);
        }
    }
};
