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

#include "InternalEvents.hpp"

#define MAX_CLIENTS 2


class Game
{
private:
    std::vector<std::shared_ptr<SClientComponent>> _clients;

    std::int32_t  _gameId;
    sf::UdpSocket _socket;
    bool          _running = false;

public:
    Game()
    {
        std::cout << "game start\n";
        _running = true;

        scene.AddEventCallback(Net::Events::CLIENT_KEY, BIND_CALLBACK(&Game::OnClientKeyEvent, this));
    };

    void Run(std::vector<std::shared_ptr<SClientComponent>> &clients, std::int32_t gameId)
    {
        std::cout << "thread start\n";
        _clients = std::move(clients);
        _gameId  = gameId;

        _socket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
        _socket.setBlocking(false);
        for (auto &client : _clients) {
            sf::Packet packet;

            packet << Net::Events::GAME_START;
            _socket.send(packet, client->ip, client->updPort);

            packet.clear();

            std::cout << "ThreadId[" << threadID() << "|port:" << _socket.getLocalPort() << "]: Launching game with "
                      << client->ip << ":" << client->updPort << "\n";

            packet << Net::Events::INITIAL_GAME_INFO;
            for (auto &client : _clients) {
                packet << client->id;
            }

            _socket.send(packet, client->ip, client->updPort);
        }

        while (_running) {
            receive();
        }
    }

    void receive()
    {
        sf::Packet remotePacket;
        EventType  type;

        sf::IpAddress remoteAddress;
        sf::Uint16    remotePort;

        sf::Socket::Status status = _socket.receive(remotePacket, remoteAddress, remotePort);
        if (status == sf::Socket::Done) {
            remotePacket >> type;
            std::cout << "ThreadId[" << threadID() << "|port:" << _socket.getLocalPort() << "]: RECEIVEDDDD\n";

            Event remoteEvent(type);
            remoteEvent.SetParam<sf::Packet>(0, remotePacket);
            scene.InvokeEvent(remoteEvent);
        }
    }

    void OnClientKeyEvent(Event &event)
    {
    }
};

// ----------------------------------------

class Matchmaker
{
private:
    bool      _isRunning = false;
    sf::Int32 _gameId;

    std::vector<std::shared_ptr<SClientComponent>> _clients;

public:
    Matchmaker() { }
    Matchmaker(sf::Int32 gameId)
    {
        _gameId = gameId;
        std::cout << "[Server] New game instance | id [" << gameId << "]\n";

        scene.AddEventCallback(Net::Events::CLIENT_DISCONNECT, BIND_CALLBACK(&Matchmaker::OnClientDisconnected, this));
    }

    ~Matchmaker() { }

    bool IsRunning() const
    {
        return _isRunning;
    }

    std::size_t GetConnectedClientsNum() const
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
            // Game game;
            Event event(Events::MATCHM_READY);
            event.SetParam<std::vector<std::shared_ptr<SClientComponent>>>(0, _clients);
            event.SetParam<sf::Int32>(1, _gameId);

            scene.InvokeEvent(event);

            // std::thread th(&Game::Run, &game, _clients, _gameId);
            // th.detach();
            // if (th.joinable())
            //     th.join();

            // workers.push_back(std::thread(&Game::Run, &game, _clients, _gameId));
            // for (auto &t : workers)
            // {
            //     t.detach();
            // }

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

    // TODO: erase clients
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

        // for (auto &it = _clients.begin(); it != _clients.end();) {
        //     if ((*it)->id == disc_clienId)
        //         _clients.erase(it);
        // }

        sf::Packet disconnectedPacket;
        disconnectedPacket << Net::Events::CLIENT_QUIT << disc_clienId << _gameId;
        BroadcastTcp(disconnectedPacket, disc_clienId);

        // TODO: erase player
        std::cout << "[Server|Game " << _gameId << "]:"
                  << " Player "
                  << disc_clienId
                  << " quit game "
                  << "\n";
    }
};
