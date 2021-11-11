/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"

#include "Nuts/Clock.hpp"

#include "System.hpp"

#include <iostream>

extern Scene scene;

class TransformSystem : public System
{
    private:

    public:

        void Init()
        {
            scene.AddEventCallback(nuts::Key::Left, BIND_CALLBACK(&TransformSystem::OnLeftkeyPressed, this));
        }

        void OnLeftkeyPressed(Event &event)
        {
            std::cout << "Left key pressed!"<< std::endl;
        }

        void Update(nuts::Clock deltaClock)
        {
            for (auto const &entity : _entities)
            {
                nuts::Vector2f pos = scene.GetComponent<TransformComponent>(entity).position;
                nuts::Vector2f vel = scene.GetComponent<VelocityComponent>(entity).velocity;
                auto &spriteComponent = scene.GetComponent<SpriteComponent>(entity);

                spriteComponent.sprite.GetSprite().setPosition({(pos.x + vel.x) * deltaClock.GetElapsedTimeAsSeconds(), (pos.y + vel.y) * deltaClock.GetElapsedTimeAsSeconds()});
            }
        }
};
