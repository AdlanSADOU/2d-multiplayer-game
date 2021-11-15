/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** EcsServer.hpp
*/

#pragma once
#include <Nuts/GameObject.hpp>

#include "Components/Components.hpp"
#include "Systems/ConnectionSystem.hpp"
#include "Systems/SClientsSystem.hpp"

Scene scene;

#define FRAMERATE (1 / 30.f)

class EcsServer {
private:
    std::shared_ptr<ConnectionSystem> _connectionSystem;
    std::shared_ptr<SClientsSystem>   _sClientSystem;
    sf::Clock                         deltaClock;

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
    }

    void Start(unsigned short port, const sf::IpAddress &address = sf::IpAddress::Any)
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
};
