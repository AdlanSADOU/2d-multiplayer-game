/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RenderSystem
*/

#pragma once

#include <System.h>
#include <SpriteComponent.h>

extern Coordinator gCoordinator;

class RenderSystem : public System // has all entities
{
private:

public:

    void Init() {

    }

    void Update(sf::RenderWindow &window) {
        for (auto const &entity : mEntities)
        {
            auto const& spriteComponent = gCoordinator.GetComponent<SpriteComponent>(entity);

            window.draw(spriteComponent.sprite);
        }
    }
};
