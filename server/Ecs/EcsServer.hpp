/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** EcsServer.hpp
*/

#pragma once
#include <Nuts/GameObject.hpp>

#include "Ecs/Components/Components.hpp"
#include "Ecs/Systems/ConnectionSystem.hpp"
#include "Ecs/Systems/SClientsSystem.hpp"

Scene gScene;

class EcsServer {
private:
    std::shared_ptr<ConnectionSystem> _connectionSystem;
    std::shared_ptr<SClientsSystem> _sClientSystem;

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
        gScene.Init();
        gScene.RegisterComponent<SClientComponent>();
        gScene.RegisterComponent<ConnectionComponent>();

        _connectionSystem = gScene.RegisterSystem<ConnectionSystem>();
        {
            EntitySignature sig;
            sig.set(gScene.GetComponentType<ConnectionComponent>());
            gScene.SetSystemSignature<ConnectionSystem>(sig);
        }

        _sClientSystem = gScene.RegisterSystem<SClientsSystem>();
        {
            EntitySignature sig;
            sig.set(gScene.GetComponentType<SClientComponent>());
            gScene.SetSystemSignature<SClientsSystem>(sig);
        }

        GameObject serverConnector;
        serverConnector.Create("serverConnector");
        serverConnector.AddComponent<ConnectionComponent>();
    }

    void Start(unsigned short port, const sf::IpAddress& address = sf::IpAddress::Any)
    {
        _connectionSystem->Init(port, address);
    }
};
