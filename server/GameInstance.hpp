/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** GameInstance.hpp
*/

#pragma once

#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <cstdint>

#define MAX_CLIENTS 4

class GameInstance {
private:
    bool      _isRunning = false;
    sf::Int32 _gameId;

    std::vector<std::shared_ptr<SClientComponent>> _clients;

public:
    GameInstance() { }
    GameInstance(sf::Int32 gameId)
    {
        _gameId = gameId;
        std::cout << "[Server] New game instance | id: " << gameId << "\n";

        scene.AddEventCallback(Net::Events::CLIENT_DISCONNECT, BIND_CALLBACK(&GameInstance::OnClientDisconnected, this));
    }

    ~GameInstance() { }

    bool IsRunning() const
    {
        return _isRunning;
    }

    std::int32_t GetConnectedClientsNum() const
    {
        return _clients.size();
    }

    void AddClient(std::shared_ptr<SClientComponent> newClient)
    {
        newClient->gameId = _gameId;
        newClient->isGame = true;

        _clients.push_back((newClient));

        // broadcast new client to all others
        for (auto &client : _clients) {
            // if (client->id != newClient->id)
            {
                sf::Packet newClientPacket;
                newClientPacket << Net::Events::NEW_CLIENT
                                << newClient->id
                                << _gameId;
                client->tcpSock->send(newClientPacket);
            }
        }
        std::cout << "[Server|Game " << _gameId << "]: "
                  << _clients.size() << " Players joined so far\n";
    }

    void Broadcast(sf::Packet packet, ClientID ignoredClientId)
    {
        for (auto &client : _clients) {
            if (client->id != ignoredClientId) {
                client->tcpSock->send(packet);
            }
        }
    }

    void OnClientDisconnected(Event &e)
    {
        sf::Packet packet = e.GetParam<sf::Packet>(0);
        ClientID   disc_clienId;
        packet >> disc_clienId;

        bool presentInGame = false;

        for (auto &client : _clients) {
            if (client->id == disc_clienId) {
                presentInGame = true;
                break;
            }
        }

        if (!presentInGame) return;

        sf::Packet disconnectedPacket;
        disconnectedPacket << Net::Events::CLIENT_QUIT << disc_clienId << _gameId;
        Broadcast(disconnectedPacket, disc_clienId);

        // TODO: erase player
        std::cout << "[Server|Game " << _gameId << "]:"
                  << " Player "
                  << disc_clienId
                  << " Quit game "
                  << "\n";
    }
};
