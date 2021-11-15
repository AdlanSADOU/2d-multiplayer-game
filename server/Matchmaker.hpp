/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Matchmaker.hpp
*/

#pragma once

#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <cstdint>
#include <thread>

#define MAX_CLIENTS 4

class Game {
private:
    std::vector<std::shared_ptr<SClientComponent>> _clients;

    std::int32_t  _gameId;
    sf::UdpSocket _socket;

public:
    Game() {};

    void Run(std::vector<std::shared_ptr<SClientComponent>> &clients, std::int32_t gameId)
    {
        _clients = std::move(clients);
        _gameId  = gameId;

        _socket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
        for (auto &client : _clients) {
            sf::Packet packet;

            std::cout << "ThreadId[" << __threadid() << "]: Launching game with "
                      << client->ip << ":" << client->updPort << "\n";

            packet << Net::Events::INITIAL_GAME_INFO << "LETS PLAYYYYY\n";
            _socket.send(packet, client->ip, client->updPort);
        }
    }
};

// ----------------------------------------

class Matchmaker {
private:
    bool      _isRunning = false;
    sf::Int32 _gameId;

    std::vector<std::shared_ptr<SClientComponent>> _clients;

public:
    Matchmaker() { }
    Matchmaker(sf::Int32 gameId)
    {
        _gameId = gameId;
        std::cout << "[Server] New game instance | id: " << gameId << "\n";

        scene.AddEventCallback(Net::Events::CLIENT_DISCONNECT, BIND_CALLBACK(&Matchmaker::OnClientDisconnected, this));
    }

    ~Matchmaker() { }

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

        for (auto &client : _clients) {
            {
                sf::Packet newClientPacket;
                newClientPacket << Net::Events::NEW_CLIENT
                                << newClient->id
                                << _gameId;
                client->tcpSock->send(newClientPacket);
            }
        }

        std::cout << "[Server|Game " << _gameId << "]: "
                  << _clients.size() << " Player(s) joined\n";

        if (_clients.size() == MAX_CLIENTS) {
            Game game;

            std::thread th(&Game::Run, &game, _clients, _gameId);
            th.join();
        }
    }

    void BroadcastTcp(sf::Packet packet, ClientID ignoredClientId)
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
        BroadcastTcp(disconnectedPacket, disc_clienId);

        // TODO: erase player
        std::cout << "[Server|Game " << _gameId << "]:"
                  << " Player "
                  << disc_clienId
                  << " Quit game "
                  << "\n";
    }
};
