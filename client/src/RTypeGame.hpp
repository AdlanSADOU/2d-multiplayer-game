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
#include "Nuts/EcsComponents/StateComponent.hpp"

#include "RTypePlayer.hpp"

#include <iostream>
#include <unordered_map>

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

class GMonster : public nuts::GameObject
{
    public:

        enum Type
        {
            GROUND = 0,
            FLY,
        };

        struct MInfos
        {
            int id;
            GMonster::Type type;
            nuts::Vector2f pos;
        };

        GMonster() {}

        GMonster(int id, GMonster::Type type, nuts::Vector2f pos, nuts::Texture &texture) {
            _infos.id = id;
            _infos.type = type;
            _infos.pos = pos;

            this->Create("Monster");
            this->AddComponent<SpriteComponent>();
            this->AddComponent<TransformComponent>();
            this->AddComponent<VelocityComponent>();
            this->AddComponent<StateComponent>();

            auto &spriteComp = GetComponent<SpriteComponent>();
            auto &transformComp = GetComponent<TransformComponent>();
            auto &stateComp = GetComponent<StateComponent>();

            transformComp.position = pos;
            spriteComp.sprite.SetTexture(texture);
            spriteComp.sprite.SetTextureRect({ 0, 0, 16, 14 });
            spriteComp.sprite.SetAnimated(true);
            spriteComp.sprite.SetLooped(true);
            spriteComp.sprite.SetFirstFrame({ 0, 0, 16, 14 });
            spriteComp.sprite.SetFrameCount(12);
            spriteComp.sprite.SetFrameTime(0.070f);
            spriteComp.sprite.InitAnimationClock();
        }

        ~GMonster() {}

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

    private:
        MInfos _infos;

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
        std::shared_ptr<nuts::Engine>           _engine;
        std::unordered_map<ClientID, GPlayer *> _players;
        std::vector<GMonster>                  _monsters;

        ClientID    _localClientId;
        GBackground _background;
        nuts::Font  _font;
        GameUI      _ui;
        std::unordered_map<GMonster::Type, nuts::Texture> _MTextures;

        bool _isRunning = false;

    public:
        RTypeGame();
        ~RTypeGame();

        void Init(std::shared_ptr<nuts::Engine> engine);
        void InitMonsterTextures();

        void SetLocalClientId(ClientID clientId);
        bool IsMonsterInList(int id);

        void Update();
        void Draw();

        void OnInitialGameInfo(Event &event);
        void OnRemoteKeyEvent(Event &event);
        void OnMonsterUpdatePos(Event &event);
};
