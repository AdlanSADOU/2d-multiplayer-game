/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include <SpriteComponent.hpp>
#include <System.hpp>

extern Scene gScene;

/**
 * Derives from System, which has a reference to all entities witch matching signature
 * RenderSystem iterates over every entity that has at least a
 * TransformComponent & SpriteComponent
 * and draws them
 **/

class RenderSystem : public System {
private:
public:
    void Init()
    {
    }

    void Update(sf::RenderWindow& window)
    {
        for (auto const& entity : _entities) {
            auto const& spriteComponent = gScene.GetComponent<SpriteComponent>(entity);

            window.draw(spriteComponent.sprite);
        }
    }
};
