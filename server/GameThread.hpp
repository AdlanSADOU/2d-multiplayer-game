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

    sf::Clock _deltaClock;
    sf::Clock _monsterSpawn;
    sf::Clock _tickrateClock;
    sf::Clock _receiveClock;
    sf::Clock _broadcastClock;
    sf::Time  _dt;

    std::vector<SMInfos> _monsters;

    int _monsterId;

    std::int32_t  _gameId;
    sf::UdpSocket _socket;
    bool          _running = false;

    std::vector<std::thread *> RecWorkers;

    sf::RenderWindow _window;
    sf::Packet       lastPacket = {};
    int32_t          _receivesPerSecond;

public:
    GameThread()
    {
        _running = true;
        srand((uint32_t)time(NULL));

        _eventManager.AddEventCallback(Net::Events::REMOTE_CLIENT_KEYS, BIND_CALLBACK(&GameThread::OnClientKeyEvent, this));
    };

    void Run(std::vector<std::shared_ptr<SClientComponent>> clients, std::int32_t gameId)
    {

        _clients = std::move(clients);
        _gameId  = gameId;

        _socket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
        _socket.setBlocking(true);

        for (auto &client : _clients) {
            sf::Packet packet;

            packet << Net::Events::GAME_START << sf::IpAddress::getLocalAddress().toInteger() << _socket.getLocalPort();
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

        sf::Time accReceiveRate;

        sf::Packet remotePacket;

        while (_running) {

            _dt = _deltaClock.restart();

            receive();

            UpdateMonsters();
        }
    }

    void receive()
    {
        sf::Packet    remotePacket;
        sf::IpAddress remoteAddress;
        sf::Uint16    remotePort;
        EventType     type;

        static sf::Time acc        = {};
        static sf::Time receiveAcc = {};
        acc += _dt;
        receiveAcc += _dt;

        sf::Socket::Status _status = _socket.receive(remotePacket, remoteAddress, remotePort);

        lastPacket = remotePacket;

        {
            auto dt = _deltaClock.getElapsedTime().asSeconds();

            if (_status == sf::Socket::Done) {
                static int receiveAccumulator = 0;
                if (receiveAcc.asSeconds() >= 1.f) {
                    _receivesPerSecond = receiveAccumulator;
                    receiveAccumulator = 0;
                    receiveAcc         = receiveAcc.Zero;
                }
                ++receiveAccumulator;

                sf::Packet tmpPacket = remotePacket;
                tmpPacket >> type;
                Event remoteEvent(type);
                remoteEvent.SetParam<sf::Packet>(0, remotePacket);
                _eventManager.InvokeEvent(remoteEvent);
            }
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

    int  i = 0;
    void OnClientKeyEvent(Event &event)
    {
        if (i < 100) {
            i++;
            return;
        }

        sf::Packet inClientKeyPacket = event.GetParam<sf::Packet>(0);

        sf::Packet tmpPacket = inClientKeyPacket;
        ClientID   clientId  = 0;

        tmpPacket >> clientId;

        Broadcast(inClientKeyPacket, clientId);
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
        tmp.x = (float)(600 + (rand() % (1000 - 600 + 1)));
        tmp.y = (float)(0 + (rand() % (400 - 0 + 1)));
        return (tmp);
    }

    nuts::Vector2f GetRandomPos()
    {
        nuts::Vector2f tmp;
        tmp.x = (float)((rand() % (800 - 0 + 1)) + 0);
        tmp.y = (float)((rand() % (400 - 0 + 1)) + 0);
        return (tmp);
    }

    void UpdateMonstersPos()
    {
        float dt = _deltaClock.getElapsedTime().asSeconds();

        for (auto &monster : _monsters) {
            nuts::Vector2f &pos     = monster.pos;
            nuts::Vector2f &gotoPos = monster.gotoPos;

            if (pos.x >= gotoPos.x + 10) { pos.x -= 100 * dt; }
            if (pos.x <= gotoPos.x - 10) { pos.x += 100 * dt; }
            if (pos.y >= gotoPos.y + 10) { pos.y -= 100 * dt; }
            if (pos.y <= gotoPos.y - 10) { pos.y += 100 * dt; }

            if ((pos.x >= gotoPos.x - 10 && pos.x <= gotoPos.x + 10) && (pos.y >= gotoPos.y - 10 && pos.y <= gotoPos.y + 10)) {
                monster.gotoPos = GetRandomPos();
            }
        }
    }

    void UpdateMonsters()
    {
        if (_monsterSpawn.getElapsedTime().asSeconds() >= 0.5f) {
            SMInfos tmp = { GetNewMId(), GetRandomType(), GetRandomPos(), GetRandomPosSpawn() };
            _monsters.emplace_back(tmp);
            _monsterSpawn.restart();
        }

        UpdateMonstersPos();

        if (_broadcastClock.getElapsedTime().asSeconds() > 1 / 16.f) {
            sf::Packet mPacket;
            mPacket << Net::Events::MONSTER_UPDATE_POS;

            for (auto &monster : _monsters) {
                mPacket << monster.id << monster.type << monster.pos.x << monster.pos.y;
            }
            Broadcast(mPacket);
            _broadcastClock.restart();
        }
    }
};