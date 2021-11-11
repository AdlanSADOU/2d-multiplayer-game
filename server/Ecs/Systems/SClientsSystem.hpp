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
public:
    SClientsSystem() {
        scene.AddEventCallback(Events::Net::CLIENT_CONN, BIND_CALLBACK(&SClientsSystem::OnClientConnected, this));
        scene.AddEventCallback(Events::Net::DISCONNECT, BIND_CALLBACK(&SClientsSystem::OnClientDisconnected, this));
     }

    /** TODO(adlan):
    *   just a draft
    */
    void OnClientConnected(Event& e)
    {
        assert(Events::Net::CLIENT_CONN == e.GetType() && "wrong event type");

        std::cout << "add that fckin client with id " << e.GetParam<std::int32_t>(0);
    };

    void OnClientDisconnected(Event& e)
    {
        assert(Events::Net::DISCONNECT == e.GetType() && "wrong event type");
        std::cout << "disconnect that fckin client\n";
    };

    void AddClient(std::string name, SClient client)
    {
        GameObject tmpClient(name);
        tmpClient.AddComponent<SClientComponent>();

        auto clientComponent = tmpClient.GetComponent<SClientComponent>();
        clientComponent.tcpSock.reset(client.tcp);
    }
};
