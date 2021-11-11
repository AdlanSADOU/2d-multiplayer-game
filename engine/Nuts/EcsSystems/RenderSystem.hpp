/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include "SpriteComponent.hpp"
#include "System.hpp"

extern Scene scene;

class RenderSystem : public System
{
    private:

    public:

        void Init() {

        }

        void Update(sf::RenderWindow &window) {
            for (auto const &entity : _entities)
            {
                auto const& spriteComponent = scene.GetComponent<SpriteComponent>(entity);

                window.draw(spriteComponent.sprite.GetSprite());
            }
        }
};
