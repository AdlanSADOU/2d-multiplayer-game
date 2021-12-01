/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypePlayer.hpp
*/

#pragma once

#include <Nuts/GameObject.hpp>
#include <Nuts/Utilities.hpp>
#include <vector>

class ProjectileManager
{
    class Projectile : public nuts::GameObject
    {
    public:
        nuts::Vector2f position = {};

        bool  isDestroyed   = false;
        bool  canFire       = true;
        float timeAlive     = 0;
        float maxTimetoLive = 4;
        float speed;
    };

    nuts::Texture           _texture = {};
    std::vector<Projectile> _projectiles;

public:
    enum Type
    {
        SMALL,
        BIG,
    };

    ProjectileManager() {};

    ProjectileManager(std::string texturePath)
    {
        if (!_texture.LoadFromFile(texturePath))
            COUT("Failed to load texture: " << texturePath);
    }

    void FireProjectile(nuts::Vector2f startPosition, Type type, float dt)
    {
        static float acc = 0;
        acc += dt;

        if (acc < .08f)
            return;
        acc = 0;

        if (type == BIG) {
            // Projectile tmpProj;
            // tmpProj.sprite.SetTexture(_texture);
            // tmpProj.sprite.SetTextureRect({ 134, 18, 32, 32 });
            // tmpProj.sprite.SetFirstFrame({ 134, 18, 32, 32 });
            // tmpProj.sprite.SetFrameCount(4);
            // tmpProj.sprite.SetFrameTime(.5f);
            // tmpProj.sprite.InitAnimationClock();
            // tmpProj.sprite.SetAnimated(true);

            // tmpProj.position = startPosition;
            // tmpProj.position.x += 20;
            // tmpProj.position.y += -6;

            // tmpProj.sprite.SetPosition(tmpProj.position);
            // tmpProj.speed = 180;

            // _projectiles.push_back(tmpProj);
        } else if (type == SMALL) {
            Projectile tmpProj;
            tmpProj.Create("small projectile");
            tmpProj.AddComponent<SpriteComponent>();
            tmpProj.AddComponent<TransformComponent>();
            tmpProj.AddComponent<VelocityComponent>();
            tmpProj.AddComponent<StateComponent>();

            auto &spriteComp    = tmpProj.GetComponent<SpriteComponent>();
            auto &transformComp = tmpProj.GetComponent<TransformComponent>();
            auto &velocityComp  = tmpProj.GetComponent<VelocityComponent>();
            auto &stateComp     = tmpProj.GetComponent<StateComponent>();

            stateComp.state       = GameState::GAME;
            velocityComp.velocity = { 0, 0 };

            spriteComp.sprite.SetTexture(_texture);
            spriteComp.sprite.SetTextureRect({ 232, 103, 16, 12 });
            spriteComp.sprite.SetFirstFrame({ 232, 103, 16, 12 });
            spriteComp.sprite.SetFrameTime(0.2f);

            spriteComp.sprite.SetAnimated(true);
            // spriteComp.sprite.SetLooped(true);
            spriteComp.sprite.SetFrameCount(2);
            spriteComp.sprite.InitAnimationClock();

            tmpProj.position = startPosition;
            tmpProj.position.x += 20;
            tmpProj.position.y += 3;

            transformComp.position = { tmpProj.position.x, tmpProj.position.y };
            tmpProj.speed          = 260;

            _projectiles.push_back(tmpProj);
        }
    }

    void Update(float dt, sf::RenderWindow &window)
    {
        int destroyedProjectileIdx = -1;

        for (int i = 0; i < _projectiles.size(); i++) {
            auto &p          = _projectiles[i];
            auto &spriteComp = p.GetComponent<SpriteComponent>();
            auto &transComp  = p.GetComponent<TransformComponent>();
            auto &velComp    = p.GetComponent<VelocityComponent>();

            if (p.timeAlive < p.maxTimetoLive)
                p.timeAlive += dt;
            else {
                destroyedProjectileIdx = i;
            }
            // spriteComp.sprite.Move((p.speed) * dt, 0);
            // transComp.position
            velComp.velocity.x = p.speed;
            // window.draw(spriteComp.sprite.GetSprite());
            // COUT("[proj]: dt: " << dt << " pos.x :" << spriteComp.sprite.x << "\n");
        }

        if (destroyedProjectileIdx != -1) {
            scene.DestroyEntity(_projectiles[destroyedProjectileIdx].GetEntity());
            _projectiles.erase(_projectiles.begin() + destroyedProjectileIdx);
        }
        // for (auto &p : _projectiles) {

        // }
    }
};

class GPlayer : public nuts::GameObject
{
    ClientID          _clientId = -1;
    nuts::Vector2f    _pos;
    nuts::Texture     _playerTexture;
    ProjectileManager _projectileManager;

public:
    VelocityComponent *_vel = nullptr;

    /**
     * left, right, up, down
     * in that order
     */
    bool _directionalKeys[4] = { 0 };

    bool       _isFiering = 0;
    sf::Uint16 _score     = 0;
    sf::Uint16 _health    = 0;
    sf::Uint16 _maxHealth = 0;

    GPlayer(ClientID id)
    {
        _clientId = id;

        Create("");
        AddComponent<SpriteComponent>();
        AddComponent<TransformComponent>();
        AddComponent<VelocityComponent>();
        AddComponent<StateComponent>();

        _playerTexture.LoadFromFile("./resources/sprites/players.gif");
        _projectileManager = ProjectileManager("./resources/sprites/r-typesheet1.gif");

        auto &spriteComp = GetComponent<SpriteComponent>();
        auto &stateComp  = GetComponent<StateComponent>();
        stateComp.state  = GameState::GAME;
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

    int GetId() const
    {
        return (_clientId);
    }

    bool IsFiering() const
    {
        return _isFiering;
    }

    nuts::Vector2f GetPosition()
    {
        auto transform = GetComponent<TransformComponent>();
        return transform.position;
    }

    void SetPosition(nuts::Vector2f pos)
    {
        auto &transform    = GetComponent<TransformComponent>();
        transform.position = { pos.x, pos.y };
    }

    void SetId(int id)
    {
        _clientId = id;
    }

    void SetFiering(bool value)
    {
        _isFiering = value;
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

    void Update(float dt, sf::RenderWindow &window)
    {
        Move();
        if (_isFiering)
            _projectileManager.FireProjectile(GetPosition(), ProjectileManager::SMALL, dt);

        _projectileManager.Update(dt, window);
    }
};