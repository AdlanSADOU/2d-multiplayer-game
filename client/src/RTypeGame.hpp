/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeGame
*/

#pragma once

#include "EcsCore/Scene.hpp"

#include "Nuts/Engine.hpp"
#include "Nuts/GameObject.hpp"

#include "Nuts/UI/Text.hpp"

#include "Nuts/Clock.hpp"
#include "Nuts/Networking.hpp"
#include "Nuts/Texture.hpp"
#include "Nuts/Vect.hpp"

#include "Nuts/EcsComponents/SpriteComponent.hpp"
#include "Nuts/EcsComponents/TransformComponent.hpp"
#include "Nuts/EcsComponents/VelocityComponent.hpp"

#include <iostream>

extern Scene scene;

#define SCROLL_SPEED 30

class GBackground
{
private:
    std::vector<nuts::GameObject> _backgrounds;
    nuts::Texture                 _texture;

public:
    GBackground() {};
    ~GBackground() {};

    void Update()
    {
        for (auto &bg : _backgrounds) {
            auto &tComp = bg.GetComponent<TransformComponent>();
            auto &vComp = bg.GetComponent<VelocityComponent>();

            float sWidth = bg.GetComponent<SpriteComponent>().sprite.GetGlobalBounds().width;

            if (tComp.position.x <= -sWidth) {
                tComp.position.x = sWidth * 2;
            }
        }
    }

    void InitBackground()
    {
        _texture.LoadFromFile("./resources/sprites/starfield.png");
        _backgrounds.emplace_back(nuts::GameObject("Background"));
        _backgrounds.emplace_back(nuts::GameObject("Background"));
        _backgrounds.emplace_back(nuts::GameObject("Background"));

        nuts::FloatRect spritePos = { 0.f, 0.f, 0.f, 0.f };
        for (auto &bg : _backgrounds) {
            bg.AddComponent<SpriteComponent>();
            bg.AddComponent<TransformComponent>();
            bg.AddComponent<VelocityComponent>();

            auto &spriteComp = bg.GetComponent<SpriteComponent>();
            auto &tComp      = bg.GetComponent<TransformComponent>();
            auto &velComp    = bg.GetComponent<VelocityComponent>();

            velComp.velocity.x = -SCROLL_SPEED;

            spriteComp.sprite.SetTexture(_texture);
            tComp.position.x = spritePos.left;
            tComp.position.y = spritePos.top;
            spritePos.left += spriteComp.sprite.GetGlobalBounds().width;
        }
    }
};

class GPlayer : public nuts::GameObject
{
    enum PlayerColor
    {
        BLUE = 0,
        RED,
        GREEN,
        PURPLE
    };

public:
    GPlayer(ClientID id)
    {
        Create("");
        AddComponent<SpriteComponent>();
        AddComponent<TransformComponent>();
        AddComponent<VelocityComponent>();

        _playerTexture.LoadFromFile("./resources/sprites/players.gif");

        auto &spriteComp = GetComponent<SpriteComponent>();
        spriteComp.sprite.SetTexture(_playerTexture);
        spriteComp.sprite.SetTextureRect({ 0, 16 * (id % 4), 32, 16 });
        spriteComp.sprite.SetAnimated(false);
        spriteComp.sprite.SetLooped(false);
        spriteComp.sprite.SetFirstFrame({ 0, 16 * (id % 4), 32, 16 });
        // sprite.SetTextureRect({0,0, 50, 50});

        _vel = &GetComponent<VelocityComponent>();

        _vel->velocity = { 0.f, 0.f };

        for (size_t i = 0; i < 4; i++) {
            _pressedKeys[i] = false;
        }
    }

    ~GPlayer()
    {
        std::cout << "player destroyed\n";
    }

    void SetId(int id)
    {
        _playerId = id;
    }

    int GetId()
    {
        return (_playerId);
    }

    void Move(nuts::Vector2f vel)
    {
        // nuts::Vector2f vel = {};
        std::cout << "moving with vel:" << vel.x << ":" << vel.y << "\n";
        // if (_pressedKeys[0])
        //     vel.x = 25;
        // else if (_pressedKeys[1])
        //     vel.x = -25;
        // else if (_pressedKeys[2])
        //     vel.y = -25;
        // else if (_pressedKeys[3])
        //     vel.y = 25;

        *_vel = { vel.x, vel.y };
    }

private:
    int            _playerId = -1;
    PlayerColor    _color;
    int            _score = 0;
    nuts::Vector2f _pos;
    nuts::Texture  _playerTexture;

public:
    VelocityComponent *_vel = nullptr;

    /**
     * right, left, up, down
     * in that order
     */
    bool _pressedKeys[4] = { 0 };
};

class GMonsters : public nuts::GameObject
{
    enum Type
    {
        GROUND = 0,
        FLY,
    };

public:
private:
    GMonsters::Type _type;
};

class RTypeGame
{
    struct GameUI
    {
        nuts::Text p1score;
        nuts::Text p2score;
        nuts::Text p3score;
        nuts::Text p4score;
    };

private:
    std::unordered_map<ClientID, GPlayer *> _players;
    std::shared_ptr<nuts::Engine>           _engine;

    ClientID    _localClientId;
    GBackground _background;
    nuts::Font  _font;
    GameUI      _ui;

    bool _isRunning = false;

public:
    RTypeGame();
    ~RTypeGame();
    void Init(std::shared_ptr<nuts::Engine> engine);
    void Update();
    void Draw();

    void SetLocalClientId(ClientID clientId)
    {
        _localClientId = clientId;
    }

    void OnInitialGameInfo(Event &event)
    {
        sf::Packet packet = event.GetParam<sf::Packet>(0);

        std::vector<ClientID> clientIds;

        while (!packet.endOfPacket()) {
            ClientID tmpId;
            packet >> tmpId;

            clientIds.push_back(tmpId);
            _players.insert({ tmpId, new GPlayer(tmpId) });

            std::cout << "[Client]: Starting game with playerId:[" << tmpId << "]\n";
        }
        _isRunning = true;
    };

    void OnRemoteKeyEvent(Event &event)
    {
        sf::Packet inClientKeyPacket = event.GetParam<sf::Packet>(0);

        ClientID  clientId;
        sf::Int32 pressedKey = -1;

        inClientKeyPacket >> clientId >> pressedKey;

        if (clientId == _localClientId)
            return;

        nuts::Vector2f vel = { 0, 0 };
        nuts::Key      key = nuts::Key::Unknown;

        if (nuts::Key::A == (nuts::Key)pressedKey) {
            vel = { -120, 0 };
        }
        if (nuts::Key::D == (nuts::Key)pressedKey) {
            vel = { 120, 0 };
        }
        if (nuts::Key::W == (nuts::Key)pressedKey)
            vel = { 0, -120 };
        if (nuts::Key::S == (nuts::Key)pressedKey)
            vel = { 0, 120 };

        // _players[clientId]->Move(vel);
        _players[clientId]->_vel->velocity = vel;
    }
};
