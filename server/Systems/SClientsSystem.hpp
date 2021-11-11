/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SClientsSystem.hpp
*/

#pragma once

#include "Nuts/EcsCore/Event.hpp"

class SClientsSystem : public System {
private:
    std::vector<GameObject> _clients;

public:
    SClientsSystem()
    {
        gScene.AddEventCallback(Events::Net::CLIENT_CONNECT, BIND_CALLBACK(&SClientsSystem::OnClientConnected, this));
        // gScene.AddEventCallback(Events::Net::CLIENT_DISCONNECT, BIND_CALLBACK(&SClientsSystem::OnClientDisconnected, this));
    }

    /** TODO(adlan):
    *   just a draft
    */
    void OnClientConnected(Event& e)
    {
        assert(Events::Net::CLIENT_CONNECT == e.GetType() && "wrong event type");
        static ClientID clientId = 0;
        auto tcpSocket = e.GetParam<std::shared_ptr<sf::TcpSocket>>(0);
        tcpSocket->setBlocking(false);

        GameObject tmpClient;
        tmpClient.Create("name");
        tmpClient.AddComponent<SClientComponent>();

        auto& clientComponent = tmpClient.GetComponent<SClientComponent>();
        clientComponent.tcpSock = tcpSocket;
        clientComponent.ip = tcpSocket->getRemoteAddress();
        clientComponent.IsConnected = true;
        clientComponent.lobbyID = 0;
        clientComponent.id = clientId;

        _clients.push_back(tmpClient);

        std::cout << "[SERVER]: client connected ID:" << clientId << " TCP:" << clientComponent.ip << ":" << clientComponent.tcpSock->getRemotePort() << std::endl;

        sf::Packet clientIdPacket;
        clientIdPacket << clientId;
        clientComponent.tcpSock->send(clientIdPacket);

        clientId++;
    };

    void OnClientDisconnected(Event& e)
    {
        assert(Events::Net::CLIENT_DISCONNECT == e.GetType() && "wrong event type");

        std::cout << "disconnect that fckin client\n";
    };

    void ReceiveTcp()
    {

        for (Entity clientEntity : _entities) {

            auto& sClientComp = gScene.GetComponent<SClientComponent>(clientEntity);
            auto tcpSock = sClientComp.tcpSock;
            if (!sClientComp.IsConnected)
                continue;

            sf::Packet remotePacket;

            sf::Socket::Status status = tcpSock->receive(remotePacket);
            if (status == sf::Socket::Done) {
                std::cout << "received " << std::endl;
            } else if (status == sf::Socket::Disconnected) {
                std::cout << "disconnected " << std::endl;
                sClientComp.IsConnected = false;
                _entities.erase(clientEntity);
                break;
            }
        }
    }
};
