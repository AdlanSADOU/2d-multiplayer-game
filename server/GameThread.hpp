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
#include <queue>

#include <Nuts/Clock.hpp>
#include <Nuts/Vect.hpp>

#include "Components/Components.hpp"

enum MonsterType
{
    GROUND = 0,
    FLY,
};
struct SMInfos
{
    int            id        = 0;
    MonsterType    type      = {};
    nuts::Vector2f pos       = {};
    nuts::Vector2f goto_pos  = {};
    bool           destroyed = 0;
};
class GameThread {
private:
    std::vector<std::shared_ptr<SClientComponent>> _clients = {};

    std::queue<sf::Packet> _client_update_packets_queue = {};

    sf::Clock _deltaClock     = {};
    sf::Clock _monsterSpawn   = {};
    sf::Clock _tickrateClock  = {};
    sf::Clock _receiveClock   = {};
    sf::Clock _broadcastClock = {};
    sf::Time  _dt             = {};

    std::vector<SMInfos> _monsters     = {};
    EventManager         _eventManager = {};
    sf::UdpSocket        _socket       = {};
    int                  _gameId       = 0;
    bool                 _running      = false;

    std::thread th_receive         = {};
    int32_t     _receivesPerSecond = 0;

public:
    GameThread();

    void Run(std::vector<std::shared_ptr<SClientComponent>> clients, std::int32_t gameId);
    void receive();
    void Broadcast(sf::Packet packet, ClientID ignoredClientId);

    void OnClientUpdate(Event &event);

    void           OnMonsterDestoyed(int destroyed_monster_id);
    MonsterType    GetRandomType();
    nuts::Vector2f GetRandomPosSpawn();
    nuts::Vector2f GetRandomPos();
    void           UpdateMonstersPos();
    void           UpdateMonsters();
};