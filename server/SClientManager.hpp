#pragma once

#include "SClient.hpp"

class SClientManager
{
private:
    std::vector<SClient> clients{};
    ClientID _clientId = 0;

public:
    std::vector<sf::TcpSocket *> clientSockets{};
    SClient &GetClientById(){

    };

    void PushClient(sf::TcpSocket &newTcpClient)
    {
        sf::TcpSocket *tcpSockPtr = new sf::TcpSocket();
        tcpSockPtr = &newTcpClient;

        printf("incomming connection\n");
        tcpSockPtr->setBlocking(false);
        clientSockets.push_back(tcpSockPtr);
    };

    void RegisterClient(sf::TcpSocket *socket)
    {
        SClient tmpClient;
        tmpClient.socket = socket;
        tmpClient.registered = true;
        tmpClient.IsInLobby = false;
        tmpClient.uuid = _clientId;
        clients.push_back(tmpClient);

        sf::Packet idPacket;
        idPacket << ERpc::CLIENT_CONNECT << tmpClient.uuid;
        socket->send(idPacket);

        ++_clientId;
        printf("client registered as ID:[%d] from | IP:[%s] | PORT:[%d]\n",
               _clientId, socket->getRemoteAddress().toString().c_str(), socket->getRemotePort());
    };

    std::vector<sf::TcpSocket *> &GetClientSockets()
    {
        return clientSockets;
    }
};
