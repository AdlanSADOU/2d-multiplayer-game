/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "System.hpp"

extern Scene scene;

class TransformSystem : public System
{
    private:

    public:

        void Init() {

        }

        void Update() {
            for (auto const &entity : _entities)
            {
                sf::Vector2f position = scene.GetComponent<TransformComponent>(entity).position;
                sf::Vector2f velocity = scene.GetComponent<VelocityComponent>(entity).velocity;
                auto &spriteComponent = scene.GetComponent<SpriteComponent>(entity);

                spriteComponent.sprite.setPosition(position + velocity);
            }
        }
};
