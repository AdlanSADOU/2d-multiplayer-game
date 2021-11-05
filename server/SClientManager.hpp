/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SclientManager.hpp
*/

#pragma once

#include <assert.h>
#include <unordered_map>

#include "Lobby.hpp"
#include "SClient.hpp"

class SClientManager {
private:
    ClientID _clientId = 0;
    Lobby lobby;

public:
    std::unordered_map<ClientID, SClient> clients {};
    void RegisterClient(sf::TcpSocket* socket);
    bool DisconnectClient(ClientID remoteId);
    void PrintConnectedClients();
};
