/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SClientsSystem.hpp
*/

#pragma once

#include "Matchmaker.hpp"
#include <Nuts/EcsCore/Event.hpp>
#include <Nuts/GameObject.hpp>

class SClientsSystem : public System {
private:
    std::vector<std::shared_ptr<Matchmaker>> _gameInstances;

public:
    SClientsSystem()
    {
        scene.AddEventCallback(Net::Events::CLIENT_CONNECT, BIND_CALLBACK(&SClientsSystem::OnClientConnected, this));
        scene.AddEventCallback(Net::Events::CLIENTS_PRINT, BIND_CALLBACK(&SClientsSystem::OnPrintConnectedClients, this));
        scene.AddEventCallback(Net::Events::CLIENT_UDP, BIND_CALLBACK(&SClientsSystem::OnClientUdpPort, this));
        scene.AddEventCallback(Net::Events::MATCHM_INIT, BIND_CALLBACK(&SClientsSystem::OnMatchmackingInit, this));
        scene.AddEventCallback(Net::Events::GAMEID_OK, BIND_CALLBACK(&SClientsSystem::OnGameIdOk, this));
        scene.AddEventCallback(Net::Events::MATCHM_PLAY, BIND_CALLBACK(&SClientsSystem::OnMatchmakingPlay, this));
        scene.AddEventCallback(Net::Events::CLIENT_DISCONNECT, BIND_CALLBACK(&SClientsSystem::OnClientDisconnected, this));
    }

    std::shared_ptr<SClientComponent> GetClientById(ClientID clientId) const
    {
        for (Entity clientEntity : _entities) {
            auto &sClientComp = scene.GetComponent<SClientComponent>(clientEntity);
            if (sClientComp.id == clientId)
                return std::make_shared<SClientComponent>(sClientComp);
        }
        return nullptr;
    }

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

                Event remoteEvent(type);
                remoteEvent.SetParam<sf::Packet>(0, remotePacket);
                scene.InvokeEvent(remoteEvent);

            } else if (status == sf::Socket::Disconnected) {
                Event remoteEvent(Net::Events::CLIENT_DISCONNECT);

                remotePacket << sClientComp.id;
                remoteEvent.SetParam<sf::Packet>(0, remotePacket);
                scene.InvokeEvent(remoteEvent);

                sClientComp.isConnected = false;
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
        clientComponent.gameId      = 0;
        clientComponent.id          = clientId;

        std::cout << "\n[SERVER]: client connected ID:" << clientId << " TCP:" << clientComponent.ip << ":" << clientComponent.tcpSock->getRemotePort() << std::endl;

        sf::Packet clientIdPacket;
        clientIdPacket << (Net::Events::CLIENT_ID) << clientId;
        clientComponent.tcpSock->send(clientIdPacket);

        clientId++;
    };

    void OnClientDisconnected(Event &e)
    {
        assert(Net::Events::CLIENT_DISCONNECT == e.GetType() && "wrong event type");

        // std::cout << "disconnect that fckin client\n";
    };

    void OnClientUdpPort(Event &e)
    {
        sf::Packet packet = e.GetParam<sf::Packet>(0);

        ClientID   remoteCliendId;
        sf::Uint16 remoteClientUdpPort;

        packet >> remoteCliendId >> remoteClientUdpPort;

        for (Entity clientEntity : _entities) {
            auto &sClientComp = scene.GetComponent<SClientComponent>(clientEntity);
            if (sClientComp.id == remoteCliendId) {
                sClientComp.updPort = remoteClientUdpPort;
                break;
            }
        }
    }

    // TODO:
    void OnMatchmackingInit(Event &e)
    {
        sf::Packet packet = e.GetParam<sf::Packet>(0);
        ClientID   remoteCliendId;
        packet >> remoteCliendId;

        static sf::Int32 gameIds = 0;
        // if (_gameInstances.size() == 0) {
        //     _gameInstances.push_back(std::make_shared<Matchmaker>(gameIds++));
        // }

        size_t nonRunningInstanceIdx = -1;
        for (size_t i = 0; i < _gameInstances.size(); i++) {
            auto &game = _gameInstances[i];

            if (!game->IsRunning()
                && game->GetConnectedClientsNum() < MAX_CLIENTS) {
                nonRunningInstanceIdx = i;
                break;
            }
        }

        if (nonRunningInstanceIdx == -1) {
            nonRunningInstanceIdx = gameIds;
            _gameInstances.push_back(std::make_shared<Matchmaker>(gameIds++));

            std::cout << "[Server] Client ["
                      << remoteCliendId
                      << "] Initiated Matchmaking\n";
        }

        if (!_gameInstances[nonRunningInstanceIdx]->IsRunning()
            && _gameInstances[nonRunningInstanceIdx]->GetConnectedClientsNum() < MAX_CLIENTS) {
            auto client = GetClientById(remoteCliendId);
            if (client) {
                _gameInstances[nonRunningInstanceIdx]->AddClient(client);
            }
        }
    }

    // TODO:
    void OnGameIdOk(Event &e)
    {
        sf::Packet packet = e.GetParam<sf::Packet>(0);

        std::cout << "[Server] OnGameIdOk\n";
    }

    // TODO:
    void OnMatchmakingPlay(Event &e)
    {
        sf::Packet packet = e.GetParam<sf::Packet>(0);

        std::cout << "[Server] OnMatchmakingPlay \n";
    }
};
