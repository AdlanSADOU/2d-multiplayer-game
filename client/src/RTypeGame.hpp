/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeGame
*/

#pragma once

#include "EcsCore/Scene.hpp"

#include "Nuts/GameObject.hpp"
#include "Nuts/Engine.hpp"

#include "Nuts/UI/Text.hpp"

#include "Nuts/Vect.hpp"
#include "Nuts/Texture.hpp"
#include "Nuts/Clock.hpp"

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
        nuts::Texture _texture;

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

            nuts::FloatRect spritePos = {0.f, 0.f, 0.f, 0.f};
            for (auto &bg : _backgrounds) {
                bg.AddComponent<SpriteComponent>();
                bg.AddComponent<TransformComponent>();
                bg.AddComponent<VelocityComponent>();

                auto &spriteComp = bg.GetComponent<SpriteComponent>();
                auto &tComp = bg.GetComponent<TransformComponent>();
                auto &velComp = bg.GetComponent<VelocityComponent>();

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
        GPlayer()
        {

        }

        ~GPlayer()
        {

        }

        void SetId(int id)
        {
            _playerId = id;
        }

        int GetId()
        {
            return (_playerId);
        }

    private:
        int _playerId = -1;
        PlayerColor _color;
        int _score = 0;
        nuts::Vector2f _pos;
};

class GMonsters : public nuts::GameObject
{
    enum Type {
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
        std::shared_ptr<nuts::Engine> _engine;
        nuts::Font _font;

        GBackground _background;
        std::vector<GPlayer> _players;
        GameUI _ui;

    public:
        RTypeGame();
        ~RTypeGame();
        void Init(std::shared_ptr<nuts::Engine> engine);
        void Update();
        void Draw();

};
