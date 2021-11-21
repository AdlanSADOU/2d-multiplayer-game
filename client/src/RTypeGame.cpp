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
    _MFrameCount.emplace(std::make_pair(GMonster::Type::FLY, 12));
    _MFrameCount.emplace(std::make_pair(GMonster::Type::GROUND, 4));
}

void RTypeGame::InitMonsterTexturesRect()
{
    _MTexturesRect.emplace(std::make_pair(GMonster::Type::FLY, (nuts::IntRect){ 0, 0, 16, 14 }));
    _MTexturesRect.emplace(std::make_pair(GMonster::Type::GROUND, (nuts::IntRect){ 0, 0, 33, 32 }));
}

void RTypeGame::InitMonsterTextures()
{
    _MTextures.emplace(std::make_pair(GMonster::Type::FLY, nuts::Texture("./resources/sprites/ball.gif")));
    _MTextures.emplace(std::make_pair(GMonster::Type::GROUND, nuts::Texture("./resources/sprites/mecha.gif")));
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

// Local client update
void RTypeGame::Update()
{
    if (!isReady) return;

    _background.Update();
    for (auto &player : _players) {
        player.second->Update();
    }
}

void RTypeGame::Draw()
{
    if (GetLocalPlayer())
        LocalClientInputs();

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

    // key presss checks
    if (_engine->IsKeyPressed(nuts::Key::Space)) {
        _players[_localClientId]->SetFiering(false);
    }
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
