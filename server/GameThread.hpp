/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** GameThread.hpp
*/

#pragma once

#include <Nuts/EcsCore/EventManager.h>
#include <SFML/System.hpp>
#include <random>
#include <thread>
#include <vector>

#include <Nuts/Clock.hpp>
#include <Nuts/EcsCore/EventManager.h>
#include <Nuts/Vect.hpp>

#include <../client/src/RTypeGame.hpp>

class GameThread
{
    struct SMInfos
    {
        int            id;
        GMonster::Type type;
        nuts::Vector2f pos;
        nuts::Vector2f gotoPos;
    };

private:
    std::vector<std::shared_ptr<SClientComponent>> _clients;
    EventManager                                   _eventManager;

    nuts::Clock _deltaClock;
    nuts::Clock _monsterSpawn;
    nuts::Clock _tickrateClock;
    nuts::Clock _receiveClock;
    nuts::Clock _broadcastClock;

    std::vector<SMInfos> _monsters;

    int _monsterId;

    std::int32_t  _gameId;
    sf::UdpSocket _socket;
    bool          _running = false;

    std::vector<std::thread *> RecWorkers;
public:
    GameThread()
    {
        _running = true;
        srand(time(NULL));

        _eventManager.AddEventCallback(Net::Events::REMOTE_CLIENT_KEYS, BIND_CALLBACK(&GameThread::OnClientKeyEvent, this));
    };

    void Run(std::vector<std::shared_ptr<SClientComponent>> clients, std::int32_t gameId)
    {
        _clients = std::move(clients);
        _gameId  = gameId;

        _socket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
        _socket.setBlocking(false);
        for (auto &client : _clients) {
            sf::Packet packet;

            packet << Net::Events::GAME_START << sf::IpAddress::getLocalAddress().toInteger() << _socket.getLocalPort();
            // _socket.send(packet, client->ip, client->updPort);
            client->tcpSock->send(packet);
            packet.clear();

            std::cout << "ThreadId[" << threadID() << "|port:" << _socket.getLocalPort() << "]: Launching game with "
                      << client->ip << ":" << client->updPort << "\n";

            packet << Net::Events::INITIAL_GAME_INFO;
            for (auto &client : _clients) {
                packet << client->id;
            }

            client->tcpSock->send(packet);
        }

        // _socket.send(packet, client->ip, client->updPort);
        while (_running) {
            if (_receiveClock.GetElapsedTimeAsSeconds() > 1 / (144.f * 2)) {
                receive();
                _receiveClock.Restart();
            }
            UpdateMonsters();
            _deltaClock.Restart();
        }
    }

    void receive()
    {
        sf::Packet remotePacket;
        EventType  type;

        sf::IpAddress remoteAddress;
        sf::Uint16    remotePort;

        sf::Socket::Status status = _socket.receive(remotePacket, remoteAddress, remotePort);

            sf::Packet packet = remotePacket;
            if (status == sf::Socket::Done) {
                remotePacket >> type;
                Event remoteEvent(type);
                remoteEvent.SetParam<sf::Packet>(0, remotePacket);
                _eventManager.InvokeEvent(remoteEvent);
            }
    }

    void Broadcast(sf::Packet packet, ClientID ignoredClientId = -1)
    {
        for (auto &client : _clients) {
            if (client->id != ignoredClientId) {
                _socket.send(packet, client->ip, client->updPort);
            }
        }
    }

    // relay key events to other clients
    void OnClientKeyEvent(Event &event)
    {
        sf::Packet inClientKeyPacket = event.GetParam<sf::Packet>(0);

        ClientID clientId;
        bool     left, right, up, down, isFiering;

        inClientKeyPacket
            >> clientId
            >> left
            >> right
            >> up
            >> down
            >> isFiering;

        sf::Packet outClientKeyPacket;

        outClientKeyPacket
            << Net::Events::REMOTE_CLIENT_KEYS
            << clientId
            << left
            << right
            << up
            << down
            << isFiering;

        Broadcast(outClientKeyPacket, clientId);
    }

    int GetNewMId()
    {
        return (_monsterId++);
    }

    GMonster::Type GetRandomType()
    {
        return ((GMonster::Type)(0 + (rand() % (1 - 0 + 1))));
    }

    nuts::Vector2f GetRandomPosSpawn()
    {
        nuts::Vector2f tmp;
        tmp.x = 600 + (rand() % (1000 - 600 + 1));
        tmp.y = 0 + (rand() % (400 - 0 + 1));
        return (tmp);
    }

    nuts::Vector2f GetRandomPos()
    {
        nuts::Vector2f tmp;
        tmp.x = (rand() % (800 - 0 + 1)) + 0;
        tmp.y = (rand() % (400 - 0 + 1)) + 0;
        return (tmp);
    }

    void UpdateMonstersPos()
    {
        float dt = _deltaClock.GetElapsedTimeAsSeconds();

        for (auto &monster : _monsters) {
            nuts::Vector2f &pos     = monster.pos;
            nuts::Vector2f &gotoPos = monster.gotoPos;

            if (pos.x >= gotoPos.x + 10) { pos.x -= 100 * dt * 2; }
            if (pos.x <= gotoPos.x - 10) { pos.x += 100 * dt * 2; }
            if (pos.y >= gotoPos.y + 10) { pos.y -= 100 * dt * 2; }
            if (pos.y <= gotoPos.y - 10) { pos.y += 100 * dt * 2; }

            if ((pos.x >= gotoPos.x - 10 && pos.x <= gotoPos.x + 10) && (pos.y >= gotoPos.y - 10 && pos.y <= gotoPos.y + 10)) {
                monster.gotoPos = GetRandomPos();
            }
        }
    }

    void UpdateMonsters()
    {
        UpdateMonstersPos();

        if (_monsterSpawn.GetElapsedTimeAsSeconds() >= 0.5f) {
            SMInfos tmp { GetNewMId(), GetRandomType(), GetRandomPos(), GetRandomPosSpawn() };
            _monsters.emplace_back(tmp);
            _monsterSpawn.Restart();
        }

        if (_broadcastClock.GetElapsedTimeAsSeconds() > 1 / 16.f) {
            sf::Packet mPacket;
            mPacket << Net::Events::MONSTER_UPDATE_POS;
            for (auto &monster : _monsters) {
                mPacket << monster.id << monster.type << monster.pos.x << monster.pos.y;
            }
            Broadcast(mPacket);
            _broadcastClock.Restart();
        }
    }
};