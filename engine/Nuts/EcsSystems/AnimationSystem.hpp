/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** AnimationSystem
*/

#pragma once

#include "Nuts/Clock.hpp"

#include "SpriteComponent.hpp"
#include "Sprite.hpp"
#include "System.hpp"

extern Scene scene;

class AnimationSystem : public System
{
    private:

    public:

        void Init() {

        }

        void Update(nuts::Clock deltaClock) {
            for (auto const &entity : _entities)
            {
                nuts::Sprite &sprite = scene.GetComponent<SpriteComponent>(entity).sprite;

                if (sprite.IsAnimated() && sprite.ShouldGetNextFrame(deltaClock.GetElapsedTimeAsSeconds())) {
                    sprite.NextFrame();
                    sprite.SetTextureRect(sprite.GetCurrentFrame());
                }
            }
        }
};
