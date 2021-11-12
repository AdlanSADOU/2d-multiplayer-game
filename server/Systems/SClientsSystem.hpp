/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SClientsSystem.hpp
*/

#pragma once

#include <Nuts/EcsCore/Event.hpp>
#include <Nuts/GameObject.hpp>

class SClientsSystem : public System
{
private:
public:
    SClientsSystem()
    {
        scene.AddEventCallback(Net::Events::CLIENT_CONNECT, BIND_CALLBACK(&SClientsSystem::OnClientConnected, this));
        scene.AddEventCallback(Net::Events::CLIENTS_PRINT, BIND_CALLBACK(&SClientsSystem::OnPrintConnectedClients, this));
        // scene.AddEventCallback(Net::Events::CLIENT_DISCONNECT, BIND_CALLBACK(&SClientsSystem::OnClientDisconnected, this));
    }

    /** TODO(adlan):
    *   just a draft
    */
    void OnClientConnected(Event &e)
    {
        assert(Net::Events::CLIENT_CONNECT == e.GetType() && "wrong event type");

        static ClientID clientId = 0;

        auto tmpSocket = e.GetParam<sf::TcpSocket *>(0);

        tmpSocket->setBlocking(false);

        nuts::GameObject tmpClient("name");
        tmpClient.AddComponent<SClientComponent>();

        auto &clientComponent   = tmpClient.GetComponent<SClientComponent>();
        clientComponent.tcpSock = std::make_shared<sf::TcpSocket>();
        clientComponent.tcpSock.reset(tmpSocket);
        clientComponent.ip          = tmpSocket->getRemoteAddress();
        clientComponent.isConnected = true;
        clientComponent.lobbyID     = 0;
        clientComponent.id          = clientId;

        std::cout << "\n[SERVER]: client connected ID:" << clientId << " TCP:" << clientComponent.ip << ":" << clientComponent.tcpSock->getRemotePort() << std::endl;

        sf::Packet clientIdPacket;
        clientIdPacket << (Net::Events::CLIENT_ID) << clientId;
        std::cout << "[Server]: Sent TCP type:"
                  << Net::Events::CLIENT_ID
                  << " id:"
                  << clientId
                  << "\n";

        clientComponent.tcpSock->send(clientIdPacket);

        clientId++;
    };

    void OnClientDisconnected(Event &e)
    {
        assert(Net::Events::CLIENT_DISCONNECT == e.GetType() && "wrong event type");

        std::cout << "disconnect that fckin client\n";
    };

    void ReceiveTcp()
    {

        sf::Packet remotePacket;
        EventType  type;

        for (Entity clientEntity : _entities) {

            auto &sClientComp = scene.GetComponent<SClientComponent>(clientEntity);
            auto  tcpSock     = sClientComp.tcpSock;

            if (!sClientComp.isConnected)
                continue;

            sf::Socket::Status status = tcpSock->receive(remotePacket);
            if (status == sf::Socket::Done) {
                remotePacket >> type;
                std::cout << "\nreceived type:"
                          << type
                          << " vs "
                          << Net::Events::CLIENT_CONNECT
                          << std::endl;

                scene.InvokeEvent(type);

            } else if (status == sf::Socket::Disconnected) { // TODO: Broadcast
                sClientComp.isConnected = false;
                std::cout << "Client id:"
                          << sClientComp.id
                          << " disconnected"
                          << "\n";
                _entities.erase(clientEntity);
                break;
            }
        }
    }

    void OnPrintConnectedClients(Event &event)
    {
        std::cout << "\n Connected clients: EventType:"
                  << event.GetType()
                  << "\n";

        for (Entity clientEntity : _entities) {

            auto &sClientComp = scene.GetComponent<SClientComponent>(clientEntity);
            auto  tcpSock     = sClientComp.tcpSock;

            std::cout << "[Server]: --> client id:"
                      << sClientComp.id
                      << " endpoint:["
                      << tcpSock->getRemoteAddress()
                      << ":"
                      << tcpSock->getRemotePort()
                      << "]\n";
        }
    }
};
