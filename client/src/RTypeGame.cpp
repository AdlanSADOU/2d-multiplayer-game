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
    std::cout << "game is_destroyed\n";

    // for (auto &c = _players.begin(); c != _players.end();)
    // {
    //     // delete &(c->second);
    //     _players.erase(c->second);
    // }
}

void RTypeGame::InitMonsterFrameCount()
{
    _MFrameCount.insert({ GMonster::Type::ORB, 12 });
    _MFrameCount.insert({ GMonster::Type::GROUND, 4 });
    _MFrameCount.insert({ GMonster::Type::REDSHIP, 8 });
}

void RTypeGame::InitMonsterTexturesRect()
{
    _MTexturesRect.insert({ GMonster::Type::ORB, { 0, 0, 16, 14 } });
    _MTexturesRect.insert({ GMonster::Type::GROUND, { 0, 0, 33, 32 } });
    _MTexturesRect.insert({ GMonster::Type::REDSHIP, { 0, 0, 33, 36 } });
}

void RTypeGame::InitMonsterTextures()
{
    _MTextures.insert({ GMonster::Type::ORB, nuts::Texture("./resources/sprites/ball.gif") });
    _MTextures.insert({ GMonster::Type::GROUND, nuts::Texture("./resources/sprites/mecha.gif") });
    _MTextures.insert({ GMonster::Type::REDSHIP, nuts::Texture("./resources/sprites/redship.gif") });
}


void RTypeGame::InitSounds()
{
    _RSounds.AddSound(RTypeSounds::Sounds::EXPLOSION, "./resources/sounds/explosion.wav");
    _RSounds.AddSound(RTypeSounds::Sounds::LASER, "./resources/sounds/laserShoot.wav");
}

void RTypeGame::InitExplosionTexture()
{
    _ExplosionTxt.LoadFromFile("./resources/sprites/explosions.gif");
}

void RTypeGame::Init(std::shared_ptr<nuts::Engine> engine)
{
    _engine = engine;
    _font.LoadFromFile("./resources/fonts/arcade.ttf");
    InitExplosionTexture();
    InitMonsterTextures();
    InitMonsterTexturesRect();
    InitMonsterFrameCount();
    InitSounds();

    _background.InitBackground();

    scene.AddEventCallback(Net::Events::INITIAL_GAME_INFO, BIND_CALLBACK(&RTypeGame::OnInitialGameInfo, this));
    scene.AddEventCallback(Net::Events::MONSTER_UPDATE_POS, BIND_CALLBACK(&RTypeGame::OnMonsterUpdatePos, this));
    scene.AddEventCallback(Net::Events::CLIENT_UPDATE_PACKETS, BIND_CALLBACK(&RTypeGame::OnRemotePlayerState, this));
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
            float pos_x;
            float pos_y;
            bool  is_destroyed = false;

            packet >> id >> type >> pos_x >> pos_y >> is_destroyed;
            if (!packet) COUT("---> ERROR: packet not fully read?\n");

            if (id < 0) {
                COUT("Error: monster id was less than 0 : " << id << "\n");
                return;
            }

            if (!is_destroyed && _monsters.find(id) == std::end(_monsters)) {
                GMonster::MInfos minfos      = { id, (GMonster::Type)type, { pos_x, pos_y } };
                nuts::Texture   &texture     = _MTextures[(GMonster::Type)type];
                nuts::IntRect    rect        = _MTexturesRect[(GMonster::Type)type];
                int              frame_count = _MFrameCount[(GMonster::Type)type];

                // note(ad): monsters are now allocated to avoid double entity destruction
                // not great but, whatever..
                GMonster *tmp = new GMonster(minfos, texture, rect, frame_count);
                _monsters.insert({ id, std::move(tmp) });
            }

            if (!is_destroyed && _monsters[id]) {
                auto &tComp = _monsters[id]->GetComponent<TransformComponent>();

                tComp                              = { pos_x, pos_y };
                _monsters[id]->_infos.is_destroyed = is_destroyed;
            }

            bool not_erased = (_monsters.find(id) != std::end(_monsters));
            if (is_destroyed && not_erased) {
                nuts::Vector2f expPos = _monsters[id]->GetComponent<TransformComponent>().position;
                AddExplosion(expPos, id);
                scene.DestroyEntity(_monsters[id]->GetEntity());
                delete _monsters[id];
                _monsters.erase(id);
                // COUT("mob erased > _destroyed_monster_id [" << _last_destroyed_monster_id << "\n");
                // COUT("mob erased > id [" << id << "\n");
            }
        }
    }
}

void RTypeGame::UpdateExplosions()
{
    for (auto e = std::begin(_RExplosions); e != std::end(_RExplosions); ++e) {
        auto &sprite = e->second->GetComponent<SpriteComponent>().sprite;
        auto &state  = e->second->GetComponent<StateComponent>().state;
        if (sprite.IsLastFrame() && state == GameState::GAME) {
            state = GameState::NONE;
            delete e->second;
            _RExplosions.erase(e);
            break;
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
    if (GetLocalPlayer()->_isFiering && !_RSounds._RSounds[RTypeSounds::LASER].IsPlaying())
        _RSounds.Play(RTypeSounds::LASER);

    _last_destroyed_monster_id = -1;

    auto it = _monsters.begin();

    while (it != _monsters.end()) {
        auto projectiles = GetLocalPlayer()->_projectileManager._projectiles;

        if (it != _monsters.cend()) {
            for (size_t j = 0; j < projectiles.size(); j++) {
                auto &spriteComp = projectiles[j].GetComponent<SpriteComponent>();

                auto const &mrect = it->second->GetComponent<SpriteComponent>().sprite.GetSprite().getGlobalBounds();

                if (spriteComp.sprite.GetSprite().getGlobalBounds().intersects(mrect)) {
                    _last_destroyed_monster_id = it->first;

                    it->second->_infos.is_destroyed = true;
                    COUT("mob marked as destroyed > id [" << _last_destroyed_monster_id << "\n");
                    if (!_RSounds._RSounds[RTypeSounds::EXPLOSION].IsPlaying())
                        _RSounds.Play(RTypeSounds::EXPLOSION);

                    // nuts::Vector2f expPos = it->second->GetComponent<TransformComponent>().position;
                    // AddExplosion(expPos, it->first);
                    // _destroyed_monster_id = it->first;
                    // scene.DestroyEntity(_monsters[it->first]->GetEntity());
                    // delete it->second;
                    // it = _monsters.erase(it);
                    break;
                }
            }
        }
        if (it != _monsters.end())
            ++it;
    }

    UpdateExplosions();
}

void RTypeGame::AddExplosion(nuts::Vector2f pos, int id)
{
    _RExplosions.insert({ id, std::move(new RExplosion(_ExplosionTxt, pos)) });
}

void RTypeGame::Draw()
{
    for (auto &p_scores : _player_scores) {
        ClientID client_id = p_scores.first;

        std::string tmp_str = "P";
        tmp_str.append(std::to_string(client_id % MAX_CLIENTS + 1));
        tmp_str.append("\n\n");
        tmp_str.append(std::to_string(_players[client_id]->_score));
        p_scores.second.SetString(tmp_str);

        p_scores.second.TEST_DRAW(_engine->window);
    }
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
