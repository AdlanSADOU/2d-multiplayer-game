/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** EcsServer.hpp
*/

#pragma once
#include <Nuts/GameObject.hpp>


#include "Components/Components.hpp"

#include "InternalEvents.hpp"

#include "Systems/ConnectionSystem.hpp"
#include "Systems/SClientsSystem.hpp"

#include "GameThread.hpp"

#include <thread>
#include <vector>

Scene scene;

#define FRAMERATE (1 / 66.f)

class EcsServer
{
private:
    std::shared_ptr<ConnectionSystem> _connectionSystem;
    std::shared_ptr<SClientsSystem>   _sClientSystem;
    sf::Clock                         deltaClock;

    std::vector<std::thread *> GameWorkers;

public:
    std::shared_ptr<ConnectionSystem> GetConnectionSystem() const
    {
        return std::shared_ptr<ConnectionSystem>(_connectionSystem);
    }

    std::shared_ptr<SClientsSystem> GetSClientsSystem() const
    {
        return std::shared_ptr<SClientsSystem>(_sClientSystem);
    }

    void Init()
    {

        scene.Init();
        scene.RegisterComponent<SClientComponent>();
        scene.RegisterComponent<ConnectionComponent>();

        _connectionSystem = scene.RegisterSystem<ConnectionSystem>();
        {
            EntitySignature sig;
            sig.set(scene.GetComponentType<ConnectionComponent>());
            scene.SetSystemSignature<ConnectionSystem>(sig);
        }

        _sClientSystem = scene.RegisterSystem<SClientsSystem>();
        {
            EntitySignature sig;
            sig.set(scene.GetComponentType<SClientComponent>());
            scene.SetSystemSignature<SClientsSystem>(sig);
        }

        nuts::GameObject serverConnector;
        serverConnector.Create("");
        serverConnector.AddComponent<ConnectionComponent>();

        scene.AddEventCallback(Events::MATCHM_READY, BIND_CALLBACK(&EcsServer::OnMatchMReady, this));
    }

    void Start(sf::Uint16 port, const sf::IpAddress &address = sf::IpAddress::Any)
    {
        _connectionSystem->Init(port, address);
        sf::Time dt;
        sf::Time acc;

        while (1) {
            dt = deltaClock.restart();
            acc += dt;

            if (acc.asSeconds() > FRAMERATE) {
                _connectionSystem->Accept();
                _connectionSystem->ReceiveUdp();

                _sClientSystem->ReceiveTcp();

                acc = sf::Time::Zero;
            }
        }
    }

    void OnMatchMReady(Event &event)
    {
        std::cout << "Matchm ready\n";
        GameThread *gameTh = new GameThread;

        sf::Int32 gameId = event.GetParam<sf::Int32>(1);

        GameWorkers.push_back(new std::thread(&GameThread::Run, gameTh, event.GetParam<std::vector<std::shared_ptr<SClientComponent>>>(0), gameId));
    }
};
