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
    float sXpos = 0;

    _ui.p1score.SetPosition({sXpos + 100, (float)winSize.y / 6 * 5});
    _ui.p2score.SetPosition({sXpos + 200, (float)winSize.y / 6 * 5});
    _ui.p3score.SetPosition({sXpos + 300, (float)winSize.y / 6 * 5});
    _ui.p4score.SetPosition({sXpos + 400, (float)winSize.y / 6 * 5});

    _background.InitBackground();
}

void RTypeGame::Update()
{
    _background.Update();
}

void RTypeGame::Draw()
{
    _ui.p1score.Draw(_engine->window);
    _ui.p2score.Draw(_engine->window);
    _ui.p3score.Draw(_engine->window);
    _ui.p4score.Draw(_engine->window);
}