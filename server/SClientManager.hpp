#pragma once

#include "SClient.hpp"

class SClientManager
{
    private:
        std::vector<SClient> clients{};
        ClientID _clientId = 0;

    public:
        std::vector<sf::TcpSocket *> _clientSockets{};

        SClient &GetClientById(ClientID id)
        {

        };

        sf::TcpSocket *GetClientSocketById(ClientID id)
        {
            for (auto c : clients)
            {
                if (c.uuid == id)
                    return c.socket;
            }
        };

        void PushClient(sf::TcpSocket &newTcpClient)
        {
            sf::TcpSocket *tcpSockPtr = new sf::TcpSocket();
            tcpSockPtr = &newTcpClient;

            printf("incomming connection\n");
            tcpSockPtr->setBlocking(false);
            _clientSockets.push_back(tcpSockPtr);
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

        void DisconnectClient(ClientID id) {
            SClient &client = GetClientById(id);
            client.registered = false;
            client.IsInLobby = false;

        };

        std::vector<sf::TcpSocket *> &GetClientSockets()
        {
            return _clientSockets;
        }
};
