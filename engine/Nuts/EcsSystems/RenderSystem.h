/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include <System.h>
#include <SpriteComponent.h>

extern Scene gScene;

/**
 * Derives from System, which has a reference to all entities.
 * RenderSystem iterates over every entity that has at least a
 * TransformComponent & SpriteComponent
 * and draws them
 **/
class RenderSystem : public System
{
private:

public:

    void Init() {

    }

    void Update(sf::RenderWindow &window) {
        for (auto const &entity : _Entities)
        {
            auto const& spriteComponent = gScene.GetComponent<SpriteComponent>(entity);

            window.draw(spriteComponent.sprite);
        }
    }
};
