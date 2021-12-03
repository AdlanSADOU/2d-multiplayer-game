/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeGame
*/

#include "RTypeGame.hpp"

RTypeGame::RTypeGame()
{
}

RTypeGame::~RTypeGame()
{
    std::cout << "game destroyed\n";

    // for (auto &c = _players.begin(); c != _players.end();)
    // {
    //     // delete &(c->second);
    //     _players.erase(c->second);
    // }
}

void RTypeGame::InitMonsterFrameCount()
{
    _MFrameCount.insert({ GMonster::Type::FLY, 12 });
    _MFrameCount.insert({ GMonster::Type::GROUND, 4 });
}

void RTypeGame::InitMonsterTexturesRect()
{
    _MTexturesRect.insert({ GMonster::Type::FLY, { 0, 0, 16, 14 } });
    _MTexturesRect.insert({ GMonster::Type::GROUND, { 0, 0, 33, 32 } });
}

void RTypeGame::InitMonsterTextures()
{
    _MTextures.insert({ GMonster::Type::FLY, nuts::Texture("./resources/sprites/ball.gif") });
    _MTextures.insert({ GMonster::Type::GROUND, nuts::Texture("./resources/sprites/mecha.gif") });
}

void RTypeGame::Init(std::shared_ptr<nuts::Engine> engine)
{
    _engine = engine;
    _font.LoadFromFile("./resources/fonts/arcade.ttf");
    InitMonsterTextures();
    InitMonsterTexturesRect();
    InitMonsterFrameCount();

    _ui.p1score = nuts::Text("0", 10, _font);
    _ui.p2score = nuts::Text("0", 10, _font);
    _ui.p3score = nuts::Text("0", 10, _font);
    _ui.p4score = nuts::Text("0", 10, _font);

    nuts::Vector2u winSize = _engine->GetWindowSize();
    float          sXpos   = 0;

    _ui.p1score.SetPosition({ sXpos + 100, (float)winSize.y / 6 * 5 });
    _ui.p2score.SetPosition({ sXpos + 200, (float)winSize.y / 6 * 5 });
    _ui.p3score.SetPosition({ sXpos + 300, (float)winSize.y / 6 * 5 });
    _ui.p4score.SetPosition({ sXpos + 400, (float)winSize.y / 6 * 5 });

    _background.InitBackground();

    scene.AddEventCallback(Net::Events::INITIAL_GAME_INFO, BIND_CALLBACK(&RTypeGame::OnInitialGameInfo, this));
    scene.AddEventCallback(Net::Events::MONSTER_UPDATE_POS, BIND_CALLBACK(&RTypeGame::OnMonsterUpdatePos, this));
    scene.AddEventCallback(Net::Events::REMOTE_CLIENT_KEYS, BIND_CALLBACK(&RTypeGame::OnRemotePlayerState, this));
}

void RTypeGame::SetLocalClientId(ClientID clientId)
{
    _localClientId = clientId;
}

void RTypeGame::ProcessMonsterPackets()
{
    for (size_t i = 0; i < _monster_packets_queue.size(); i++) {
        sf::Packet packet = _monster_packets_queue.front();
        _monster_packets_queue.pop();

        while (!packet.endOfPacket()) {
            int   id = -1;
            int   type;
            float posX;
            float posY;
            bool  destroyed = false;

            packet >> id >> type >> posX >> posY >> destroyed;

            if (id < 0) {
                COUT("Error: monster id was less than 0 : " << id << "\n");
                return;
            }

            if (!destroyed && _monsters.find(id) == std::end(_monsters)) {
                GMonster::MInfos minfos      = { id, (GMonster::Type)type, { posX, posY } };
                nuts::Texture   &texture     = _MTextures[(GMonster::Type)type];
                nuts::IntRect    rect        = _MTexturesRect[(GMonster::Type)type];
                int              frame_count = _MFrameCount[(GMonster::Type)type];

                // note(ad): monsters are now allocated to avoid double entity destruction
                GMonster *tmp = new GMonster(minfos, texture, rect, frame_count);
                _monsters.insert({ id, std::move(tmp) });
            }

            if (!destroyed && _monsters[id]) {
                auto &tComp      = _monsters[id]->GetComponent<TransformComponent>();
                auto &spriteComp = _monsters[id]->GetComponent<SpriteComponent>();

                tComp                              = { posX, posY };
                _monsters[id]->_infos.is_destroyed = destroyed;
            }

            if (destroyed && (_monsters.find(id) != std::end(_monsters))) {
                scene.DestroyEntity(_monsters[id]->GetEntity());
                delete _monsters[id];
                _monsters[id] = nullptr;
                _monsters.erase(id);

                COUT("[UDP-REC]: depop monster with id: " << id << "\n");
                continue;
            }
        }
    }
}

// Local client update
void RTypeGame::Update()
{
    if (!isReady) return;

    if (GetLocalPlayer())
        LocalClientInputs();

    _background.Update();

    ProcessMonsterPackets();

    for (auto &player : _players) {
        player.second->Update(_engine->dt, _engine->window);
    }

    _destroyed_monster_id = -1;

    for (auto &m : _monsters) {
        if (!m.second || m.first < 0) break;
        // this entity could be destroyed by receive() thread while accessing it here
        if (m.second->GetEntity() < 0 || m.second->GetEntity() > MAX_ENTITIES) continue;

        auto projectiles = GetLocalPlayer()->_projectileManager._projectiles;

        for (size_t j = 0; j < projectiles.size(); j++) {
            auto &spriteComp = projectiles[j].GetComponent<SpriteComponent>();

            if (m.second) {
                auto const &mrect = m.second->GetComponent<SpriteComponent>().sprite.GetSprite().getGlobalBounds();
                if (spriteComp.sprite.GetSprite().getGlobalBounds().intersects(mrect)) {
                    _destroyed_monster_id = m.first;
                    break;
                }
            }
        }
    }
}

void RTypeGame::Draw()
{
    _ui.p1score.TEST_DRAW(_engine->window);
    _ui.p2score.TEST_DRAW(_engine->window);
    _ui.p3score.TEST_DRAW(_engine->window);
    _ui.p4score.TEST_DRAW(_engine->window);
}

void RTypeGame::LocalClientInputs()
{
    if (_players.size() == 0 && !_players[_localClientId]) return;

    // key release checks go first
    if (_engine->IsKeyReleased(nuts::Key::A)) {
        _players[_localClientId]->_directionalKeys[0] = false;
    }
    if (_engine->IsKeyReleased(nuts::Key::D)) {
        _players[_localClientId]->_directionalKeys[1] = false;
    }
    if (_engine->IsKeyReleased(nuts::Key::W)) {
        _players[_localClientId]->_directionalKeys[2] = false;
    }
    if (_engine->IsKeyReleased(nuts::Key::S)) {
        _players[_localClientId]->_directionalKeys[3] = false;
    }
    if (_engine->IsKeyReleased(nuts::Key::Space)) {
        _players[_localClientId]->SetFiering(false);
    }

    // ----------
    if (_engine->IsKeyPressed(nuts::Key::A)) {
        _players[_localClientId]->_directionalKeys[0] = true;
    }
    if (_engine->IsKeyPressed(nuts::Key::D)) {
        _players[_localClientId]->_directionalKeys[1] = true;
    }
    if (_engine->IsKeyPressed(nuts::Key::W)) {
        _players[_localClientId]->_directionalKeys[2] = true;
    }
    if (_engine->IsKeyPressed(nuts::Key::S)) {
        _players[_localClientId]->_directionalKeys[3] = true;
    }

    if (_engine->IsKeyPressed(nuts::Key::Space)) {
        _players[_localClientId]->SetFiering(true);
    }
}
