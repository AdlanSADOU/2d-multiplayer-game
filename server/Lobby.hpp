/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Lobby.hpp
*/

#pragma once

#include <vector>

#include <Nuts/Networking.hpp>
#include "SClient.hpp"

#define MAX_CLIENTS 4

class Lobby {
private:
    std::vector<std::shared_ptr<SClient>> _clients;
    sf::Uint8 _id;

public:
    void AddClient(SClient* client)
    {

        if (_clients.size() == MAX_CLIENTS)
            return;

        std::shared_ptr<SClient> tmpClientPtr;
        tmpClientPtr.reset(client);
        _clients.push_back(tmpClientPtr);

        // sf::Packet packet;
        // packet << RPC(ERpc::LOBBY_ID);

        // sf::IpAddress ip = client->tcp->getRemoteAddress();
        // sf::Uint16 port = client->tcp->getRemotePort();
        // if (client->upd->bind(port, ip) != sf::Socket::Done)
        //     printf("upd bind error\n");
        // if (client->upd->send(packet, ip, port) != sf::Socket::Done)
        //     printf("upd send error\n");
    };
};
