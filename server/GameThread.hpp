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

struct ClientData
{
    int32_t _score     = 0;
    int32_t _health    = 0;
    int32_t _maxHealth = 0;
};
class GameThread {

    std::vector<std::shared_ptr<SClientComponent>> _clients     = {};
    std::unordered_map<ClientID, ClientData>       _clientsData = {};

    // std::queue<sf::Packet> _client_update_packets_queue = {}; deprecated

    sf::Clock _deltaClock     = {};
    sf::Clock _monsterSpawn   = {};
    sf::Clock _tickrateClock  = {};
    sf::Clock _receiveClock   = {};
    sf::Clock _broadcastClock = {};
    sf::Time  _dt             = {};

    std::vector<SMInfos> _monsters                   = {};
    EventManager         _eventManager               = {};
    sf::UdpSocket        _socket                     = {};
    int                  _gameId                     = 0;
    bool                 _running                    = false;
    int                  tick_count = 0;

    std::thread th_receive         = {};
    int32_t     _receivesPerSecond = 0;

    void Receive();
    void Broadcast(sf::Packet packet, ClientID ignoredClientId);

    void OnClientUpdate(Event &event);

    void           OnMonsterDestoyed(int destroyed_monster_id, ClientID client_id);
    MonsterType    GetRandomType();
    nuts::Vector2f GetRandomPosSpawn();
    nuts::Vector2f GetRandomPos();
    void           UpdateMonstersPos();
    void           UpdateMonsters();

public:
    GameThread();

    void Run(std::vector<std::shared_ptr<SClientComponent>> clients, std::int32_t gameId);
};