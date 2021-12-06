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
#include "Nuts/Audio.hpp"

#include "Nuts/EcsComponents/SpriteComponent.hpp"
#include "Nuts/EcsComponents/TransformComponent.hpp"
#include "Nuts/EcsComponents/VelocityComponent.hpp"
#include "Nuts/EcsComponents/StateComponent.hpp"
#include "Nuts/EcsComponents/SoundComponent.hpp"

#include "RTypePlayer.hpp"
#include "../client/src/RGameState.hpp"

#include <iostream>
#include <unordered_map>
#include <algorithm>

extern Scene scene;

#define SCROLL_SPEED 30

class GBackground {
private:
    std::vector<nuts::GameObject> _backgrounds;
    nuts::Texture                 _planets;
    nuts::Texture                 _stars;

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

    void AddLayer(const std::string &name, int layerCount)
    {
        for (int i = 0; i < layerCount; ++i) {
            auto bg = nuts::GameObject(name);
            bg.AddComponent<SpriteComponent>();
            bg.AddComponent<TransformComponent>();
            bg.AddComponent<VelocityComponent>();
            bg.AddComponent<StateComponent>();
            _backgrounds.emplace_back(bg);
        }
    }

    void InitPlanets()
    {
        nuts::FloatRect spritePos = { 0.f, 0.f, 0.f, 0.f };
        for (auto &bg : _backgrounds) {
            if (bg.GetName().compare("Planets")) {
                auto &spriteComp = bg.GetComponent<SpriteComponent>();
                auto &tComp      = bg.GetComponent<TransformComponent>();
                auto &velComp    = bg.GetComponent<VelocityComponent>();
                auto &stateComp  = bg.GetComponent<StateComponent>();
                stateComp.state  = GAME;
                spriteComp.sprite.SetTexture(_planets);
                spriteComp.sprite.SetScale({ 2.2f, 2.2f });
                velComp.velocity.x = -SCROLL_SPEED;
                tComp.position.x   = spritePos.left;
                tComp.position.y   = spritePos.top;
                spritePos.left += spriteComp.sprite.GetGlobalBounds().width;
            }
        }
    }

    void InitStars()
    {
        nuts::FloatRect spritePos = { 0.f, 0.f, 0.f, 0.f };
        for (auto &bg : _backgrounds) {
            if (bg.GetName().compare("Stars")) {
                auto &spriteComp = bg.GetComponent<SpriteComponent>();
                auto &tComp      = bg.GetComponent<TransformComponent>();
                auto &velComp    = bg.GetComponent<VelocityComponent>();
                auto &stateComp  = bg.GetComponent<StateComponent>();
                stateComp.state  = GAME;
                spriteComp.sprite.SetTexture(_stars);
                velComp.velocity.x = -SCROLL_SPEED * 1.5;
                tComp.position.x   = spritePos.left;
                tComp.position.y   = spritePos.top;
                spritePos.left += spriteComp.sprite.GetGlobalBounds().width;
            }
        }
    }

    void InitLayers()
    {
        InitPlanets();
        InitStars();
    }

    void InitBackground()
    {
        _planets.LoadFromFile("./resources/sprites/planets.png");
        _stars.LoadFromFile("./resources/sprites/stars.png");

        AddLayer("Stars", 3);
        AddLayer("Planets", 3);
        InitLayers();
    }
};

class GMonster : public nuts::GameObject {
public:
    enum Type
    {
        GROUND = 0,
        ORB,
        REDSHIP
    };

    struct MInfos
    {
        int            id;
        GMonster::Type type;
        nuts::Vector2f pos;
        bool           is_destroyed = false;
    };

    GMonster() { }

    GMonster(MInfos infos, nuts::Texture &texture, nuts::IntRect rect, int fc)
    {
        _infos = infos;

        this->Create("Monster");
        this->AddComponent<SpriteComponent>();
        this->AddComponent<TransformComponent>();
        this->AddComponent<VelocityComponent>();
        this->AddComponent<StateComponent>();

        auto &spriteComp    = GetComponent<SpriteComponent>();
        auto &transformComp = GetComponent<TransformComponent>();
        auto &velocityComp  = GetComponent<VelocityComponent>();
        auto &stateComp     = GetComponent<StateComponent>();

        stateComp.state        = GameState::GAME;
        transformComp.position = _infos.pos;
        velocityComp.velocity  = { 0, 0 };
        spriteComp.sprite.SetTexture(texture);
        spriteComp.sprite.SetTextureRect(rect);
        spriteComp.sprite.SetAnimated(true);
        spriteComp.sprite.SetLooped(true);
        spriteComp.sprite.SetFirstFrame(rect);
        spriteComp.sprite.SetFrameCount(fc);
        spriteComp.sprite.SetFrameTime(0.070f);
        spriteComp.sprite.InitAnimationClock();
    }

    ~GMonster()
    {
        // COUT("[ENTT]: monster destroyed with id: [" << GetEntity() << "\n");
        // scene.DestroyEntity(GetEntity());
    }

    GMonster::Type GetType()
    {
        return (_infos.type);
    }

    void SetType(GMonster::Type type)
    {
        _infos.type = type;
    }

    nuts::Vector2f GetPosition()
    {
        return (_infos.pos);
    }

    void SetPosition(nuts::Vector2f pos)
    {
        _infos.pos = pos;
    }

    int GetId()
    {
        return (_infos.id);
    }

    void SetId(int id)
    {
        _infos.id = id;
    }

    MInfos _infos;

private:
};

class RTypeSounds {

public:
    enum Sounds
    {
        LASER,
        EXPLOSION
    };

    RTypeSounds()
    {
    }

    ~RTypeSounds()
    {
    }

    void AddSound(RTypeSounds::Sounds soundType, const std::string &path)
    {
        _RSoundBufs.insert(std::make_pair(soundType, new nuts::SoundBuffer(path)));
        _RSounds.insert(std::make_pair(soundType, nuts::Sound(*_RSoundBufs[soundType])));
    }

    void Play(RTypeSounds::Sounds soundType)
    {
        _RSounds[soundType].Play();
    }

public:
    std::unordered_map<RTypeSounds::Sounds, nuts::SoundBuffer *> _RSoundBufs;
    std::unordered_map<RTypeSounds::Sounds, nuts::Sound>         _RSounds;
};

class RExplosion : public nuts::GameObject {
public:
    RExplosion() { }

    RExplosion(nuts::Texture &txt)
    {
        Create("Explosion");

        AddComponent<StateComponent>();
        AddComponent<SpriteComponent>();
        AddComponent<VelocityComponent>();
        AddComponent<TransformComponent>();

        auto &stateComp = GetComponent<StateComponent>();
        auto &sprite    = GetComponent<SpriteComponent>().sprite;
        auto &velocity  = GetComponent<VelocityComponent>().velocity;
        auto &pos       = GetComponent<TransformComponent>().position;

        stateComp.state = GameState::GAME;

        pos      = { 0, 0 };
        velocity = { 0, 0 };
        sprite.SetTexture(txt);
        sprite.SetTextureRect({ 128, 0, 33, 33 });
        sprite.SetFirstFrame({ 128, 0, 33, 33 });
        sprite.SetAnimated(true);
        sprite.SetFrameTime(0.05f);
        sprite.SetFrameCount(6);
        sprite.InitAnimationClock();
    }

    RExplosion(nuts::Texture &txt, nuts::Vector2f pos)
        : RExplosion(txt)
    {
        SetPosition(pos);
    }

    ~RExplosion()
    {
        scene.DestroyEntity(GetEntity());
    }

    void SetPosition(nuts::Vector2f pos)
    {
        auto &position = GetComponent<TransformComponent>().position;

        position = pos;
    }

private:
};

class RTypeGame {

private:
    std::shared_ptr<nuts::Engine>            _engine;
    std::unordered_map<ClientID, GPlayer *>  _players;
    std::unordered_map<ClientID, nuts::Text> _player_scores;

    std::unordered_map<int, GMonster *> _monsters;
    std::queue<sf::Packet>              _monster_packets_queue;

    nuts::Texture                       _ExplosionTxt;
    std::unordered_map<int, RExplosion *> _RExplosions;
    RTypeSounds                         _RSounds;

    ClientID    _localClientId;
    GBackground _background;
    nuts::Font  _font;

    std::unordered_map<GMonster::Type, nuts::Texture> _MTextures;
    std::unordered_map<GMonster::Type, nuts::IntRect> _MTexturesRect;
    std::unordered_map<GMonster::Type, int>           _MFrameCount;

    bool _isRunning = false;
    void LocalClientInputs();

public:
    int _last_destroyed_monster_id = -1;

    RTypeGame();
    ~RTypeGame();

    void Init(std::shared_ptr<nuts::Engine> engine);
    void InitMonsterTextures();
    void InitMonsterTexturesRect();
    void InitMonsterFrameCount();
    void InitSounds();
    void InitExplosionTexture();

    void SetLocalClientId(ClientID clientId);
    bool IsMonsterInList(int id);
    void AddExplosion(nuts::Vector2f pos, int id);

    void Update();
    void UpdateExplosions();
    void ProcessMonsterPackets();
    void Draw();

    void OnInitialGameInfo(Event &event);
    void OnRemoteKeyEvent(Event &event);
    void OnMonsterUpdatePos(Event &event);

    GPlayer *GetLocalPlayer()
    {
        if (!isReady) {
            return nullptr;
        }

        return _players.at(_localClientId);
    }

    void OnRemotePlayerState(Event &event);

    bool isReady = false;
};
