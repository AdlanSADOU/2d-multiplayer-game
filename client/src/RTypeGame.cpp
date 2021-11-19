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

void RTypeGame::Init(std::shared_ptr<nuts::Engine> engine)
{
    _engine = engine;
    _font.LoadFromFile("./resources/fonts/arcade.ttf");

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
    scene.AddEventCallback(Net::Events::CLIENT_KEY, BIND_CALLBACK(&RTypeGame::OnRemoteKeyEvent, this));
}

void RTypeGame::Update()
{
    if (!_isRunning) return;

    _background.Update();

    for (auto &remotePlayer : _players) {
        // remotePlayer.second->Move();
    }

    nuts::Vector2f vel = {};
    nuts::Key      key = {};

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    //     _players[_localClientId]->_pressedKeys[0] = true;
    //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    //     _players[_localClientId]->_pressedKeys[1] = true;
    //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    //     _players[_localClientId]->_pressedKeys[2] = true;
    //  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    //     _players[_localClientId]->_pressedKeys[3] = true;

    if (_engine->IsKeyPressed(nuts::Key::A)) {
        vel = { -50, 0 };
    }
    if (_engine->IsKeyPressed(nuts::Key::D)) {
        vel = { 50, 0 };
        std::cout << "HELLO\n";
    }
    if (_engine->IsKeyPressed(nuts::Key::W))
        vel = { 0, -50 };
    if (_engine->IsKeyPressed(nuts::Key::S))
        vel = { 0, 50 };

    _players[_localClientId]->Move(vel);
}

void RTypeGame::Draw()
{
    _ui.p1score.Draw(_engine->window);
    _ui.p2score.Draw(_engine->window);
    _ui.p3score.Draw(_engine->window);
    _ui.p4score.Draw(_engine->window);
}
