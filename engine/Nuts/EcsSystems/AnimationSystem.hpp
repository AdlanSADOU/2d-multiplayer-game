/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** AnimationSystem
*/

#pragma once

#include "Nuts/Clock.hpp"

#include "SpriteComponent.hpp"
#include "StateComponent.hpp"

#include "Sprite.hpp"
#include "System.hpp"

#include "../client/src/RGameState.hpp"

extern Scene scene;

class AnimationSystem : public System
{
    private:

    public:

        void Init()
        {

        }

        void Update(nuts::Clock deltaClock, GameState currentState)
        {
            for (auto const &entity : _entities) {
                auto &stateComponent = scene.GetComponent<StateComponent>(entity);

                if (stateComponent.state == currentState) {
                    nuts::Sprite &sprite = scene.GetComponent<SpriteComponent>(entity).sprite;

                    if (sprite.IsAnimated() && sprite.ShouldGetNextFrame(sprite.GetAnimationClock()->GetElapsedTimeAsSeconds())) {
                        sprite.NextFrame();
                        sprite.SetTextureRect(sprite.GetCurrentFrame());
                        sprite.ResetAnimationClock();
                    }
                }
            }
        }
};
