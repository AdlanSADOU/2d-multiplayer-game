/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypePlayer.hpp
*/

#pragma once

#include <Nuts/GameObject.hpp>

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
        _clientId = id;

        Create("");
        AddComponent<SpriteComponent>();
        AddComponent<TransformComponent>();
        AddComponent<VelocityComponent>();
        AddComponent<StateComponent>();

        _playerTexture.LoadFromFile("./resources/sprites/players.gif");

        auto &spriteComp = GetComponent<SpriteComponent>();
        auto &stateComp = GetComponent<StateComponent>();
        stateComp.state = GameState::GAME;
        spriteComp.sprite.SetTexture(_playerTexture);
        spriteComp.sprite.SetTextureRect({ 0, 16 * (id % MAX_CLIENTS), 32, 16 });
        spriteComp.sprite.SetAnimated(false);
        spriteComp.sprite.SetLooped(false);
        spriteComp.sprite.SetFirstFrame({ 0, 16 * (id % MAX_CLIENTS), 32, 16 });

        _vel = &GetComponent<VelocityComponent>();

        _vel->velocity = { 0.f, 0.f };

        for (size_t i = 0; i < 4; i++) {
            _directionalKeys[i] = false;    
        }
    }

    ~GPlayer()
    {
        std::cout << "player destroyed\n";
    }

    void SetId(int id)
    {
        _clientId = id;
    }

    int GetId()
    {
        return (_clientId);
    }

    void SetFiering(bool value)
    {
        _isFiering = value;
    }

    bool IsFiering() const
    {
        return _isFiering;
    }

    void Move()
    {
        nuts::Vector2f vel = {};

        if (_directionalKeys[0])
            vel.x = -125;
        if (_directionalKeys[1])
            vel.x = 125;
        if (_directionalKeys[2])
            vel.y = -125;
        if (_directionalKeys[3])
            vel.y = 125;

        *_vel = { vel.x, vel.y };
    }

    void Update()
    {
        Move();
    }

private:
    ClientID       _clientId = -1;
    nuts::Vector2f _pos;
    nuts::Texture  _playerTexture;

public:
    VelocityComponent *_vel = nullptr;

    /**
     * left, right, up, down
     * in that order
     */
    bool       _directionalKeys[4] = { 0 };

    bool       _isFiering          = false;
    sf::Uint16 _score              = 0;
    sf::Uint16 _health             = 0;
    sf::Uint16 _maxHealth          = 0;
};