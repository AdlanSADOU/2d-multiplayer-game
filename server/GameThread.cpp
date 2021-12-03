#include "GameThread.hpp"

#include <Nuts/Utilities.hpp>

GameThread::GameThread()
{
    _running = true;
    srand((uint32_t)time(NULL));

    _eventManager.AddEventCallback(Net::Events::CLIENT_UPDATE_PACKETS, BIND_CALLBACK(&GameThread::OnClientUpdate, this));
};

void GameThread::Run(std::vector<std::shared_ptr<SClientComponent>> clients, std::int32_t gameId)
{
    _clients = std::move(clients);
    _gameId  = gameId;

    _socket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
    _socket.setBlocking(true);

    for (auto &client : _clients) {
        sf::Packet packet;

        packet << Net::Events::GAME_START << sf::IpAddress::getLocalAddress().toInteger() << _socket.getLocalPort();
        COUT("sent eventType: " << Net::Events::GAME_START);
        client->tcpSock->send(packet);
        packet.clear();

        std::cout << "ThreadId[" << threadID() << "|port:" << _socket.getLocalPort() << "]: Launching game with "
                  << client->ip << ":" << client->updPort << "\n";

        packet << Net::Events::INITIAL_GAME_INFO;
        for (auto &client : _clients) {
            packet << client->id;
        }

        client->tcpSock->send(packet);
        COUT("sent eventType: " << Net::Events::INITIAL_GAME_INFO);
    }

    sf::Time accReceiveRate;

    // th_receive = std::thread(&GameThread::receive, this);

    while (_running) {

        _dt = _deltaClock.restart();

        receive();

        UpdateMonsters();
    }

    th_receive.join();
}

void GameThread::receive()
{
    // while (_running)
    {
        sf::Packet    remotePacket;
        sf::IpAddress remoteAddress;
        sf::Uint16    remotePort;
        EventType     type;

        thread_local sf::Time acc        = {};
        thread_local sf::Time receiveAcc = {};
        acc += _dt;
        receiveAcc += _dt;

        sf::Socket::Status _status = _socket.receive(remotePacket, remoteAddress, remotePort);

        {
            auto dt = _deltaClock.getElapsedTime().asSeconds();

            if (_status == sf::Socket::Done) {
                thread_local int receiveAccumulator = 0;
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
}

void GameThread::Broadcast(sf::Packet packet, ClientID ignoredClientId = -1)
{
    for (auto &client : _clients) {
        if (client->id != ignoredClientId) {
            _socket.send(packet, client->ip, client->updPort);
        }
    }
}

int  i = 0;
void GameThread::OnClientUpdate(Event &event)
{
    if (i < 100) {
        i++;
        return;
    }

    bool  key_left             = 0;
    bool  key_right            = 0;
    bool  key_up               = 0;
    bool  key_down             = 0;
    float x                    = 0;
    float y                    = 0;
    bool  is_fiering           = 0;
    int   destroyed_monster_id = -1;

    sf::Packet inClientKeyPacket = event.GetParam<sf::Packet>(0);

    sf::Packet tmpPacket = inClientKeyPacket;
    EventType  type;
    ClientID   clientId = 0;

    tmpPacket >> type
        >> clientId
        >> key_left
        >> key_right
        >> key_up
        >> key_down
        >> x
        >> y
        >> is_fiering
        >> destroyed_monster_id;

    // COUT(
    //     clientId
    //     << key_left
    //     << key_right
    //     << key_up
    //     << key_down
    //     << x
    //     << y
    //     << is_fiering
    //     << destroyed_monster_id << "\n");

    if (destroyed_monster_id != -1) {
        COUT("received destroyed_monster_id: " << destroyed_monster_id << "\n");
        OnMonsterDestoyed(destroyed_monster_id);
    }

    Broadcast(inClientKeyPacket, clientId);
}

void GameThread::OnMonsterDestoyed(int destroyed_monster_id)
{
    thread_local int last_destroyed_id = -1;
    // if (last_destroyed_id == destroyed_monster_id)
    //     return;

    for (auto it = _monsters.begin(); it != _monsters.end();) {
        if (it->id == destroyed_monster_id) {
            COUT("marking as destroyed > monster with id: " << it->id << "\n");
            // we just mark the monster with matching id as being destroyed
            // it will eventually get erased in UpdateMonsters()
            it->destroyed = true;
            return;
        } else {
            ++it;
        }
    }
}

MonsterType GameThread::GetRandomType()
{
    return ((MonsterType)(0 + (rand() % (1 - 0 + 1))));
}

nuts::Vector2f GameThread::GetRandomPosSpawn()
{
    nuts::Vector2f tmp;
    tmp.x = (float)(600 + (rand() % (1000 - 600 + 1)));
    tmp.y = (float)(0 + (rand() % (400 - 0 + 1)));
    return (tmp);
}

nuts::Vector2f GameThread::GetRandomPos()
{
    nuts::Vector2f tmp;
    tmp.x = (float)((rand() % (800 - 0 + 1)) + 0);
    tmp.y = (float)((rand() % (400 - 0 + 1)) + 0);
    return (tmp);
}

void GameThread::UpdateMonstersPos()
{
    float dt = _deltaClock.getElapsedTime().asSeconds();

    for (auto &monster : _monsters) {
        nuts::Vector2f &pos      = monster.pos;
        nuts::Vector2f &goto_pos = monster.goto_pos;

        if (pos.x >= goto_pos.x + 10) { pos.x -= 50 * dt; }
        if (pos.x <= goto_pos.x - 10) { pos.x += 50 * dt; }
        if (pos.y >= goto_pos.y + 10) { pos.y -= 50 * dt; }
        if (pos.y <= goto_pos.y - 10) { pos.y += 50 * dt; }

        if ((pos.x >= goto_pos.x - 10 && pos.x <= goto_pos.x + 10) && (pos.y >= goto_pos.y - 10 && pos.y <= goto_pos.y + 10)) {
            monster.goto_pos = GetRandomPos();
        }
    }
}

void GameThread::UpdateMonsters()
{
    thread_local int monster_id = 0;

    if (_monsters.size() < 30 && _monsterSpawn.getElapsedTime().asSeconds() >= 0.9f) {
        COUT("spawned monster with id: " << monster_id << "\n");
        SMInfos tmp = { monster_id, GetRandomType(), GetRandomPos(), GetRandomPosSpawn() };
        _monsters.emplace_back(tmp);
        _monsterSpawn.restart();
        ++monster_id;
    }

    UpdateMonstersPos();

    if (_broadcastClock.getElapsedTime().asSeconds() > 1 / 22.f) {
        sf::Packet mPacket;
        mPacket << Net::Events::MONSTER_UPDATE_POS;

        for (auto &monster : _monsters) {
            mPacket << monster.id << monster.type << monster.pos.x << monster.pos.y << monster.destroyed;
        }

        Broadcast(mPacket);
        _broadcastClock.restart();
    }

    thread_local int i = 0;

    if (i >= 600)
        for (auto it = _monsters.begin(); it != _monsters.end();) {
            if (it->destroyed) {
                COUT("erased > monster with id: " << it->id << "\n");
                it = _monsters.erase(it);
                i  = 0;
            } else {
                ++it;
            }
        }
    ++i;
}