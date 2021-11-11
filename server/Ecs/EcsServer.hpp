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

Scene scene;

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

        GameObject serverConnector("serverConnector");
        serverConnector.AddComponent<ConnectionComponent>();
    }

    void Start(unsigned short port, const sf::IpAddress& address = sf::IpAddress::Any)
    {
        _connectionSystem->Init(port, address);
    }
};
