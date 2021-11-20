/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include "SpriteComponent.hpp"
#include "StateComponent.hpp"
#include "System.hpp"

extern Scene scene;

class RenderSystem : public System
{
    private:

    public:

        void Init()
        {

        }

        void Update(sf::RenderWindow &window, GameState currentState)
        {
            for (auto const &entity : _entities)
            {
                auto &stateComponent = scene.GetComponent<StateComponent>(entity);

                if (stateComponent.state == currentState) {
                    auto const& spriteComponent = scene.GetComponent<SpriteComponent>(entity);

                    window.draw(spriteComponent.sprite.GetSprite());
                }
            }
        }
};
