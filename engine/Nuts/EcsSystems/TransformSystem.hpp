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
        scene.AddEventCallback(nuts::Key::LeftArrow, BIND_CALLBACK(&TransformSystem::OnLeftkeyPressed, this));
    }

    void OnLeftkeyPressed(Event &event)
    {
        // std::cout << "Left key pressed!" << std::endl;
    }

    void Update(nuts::Clock deltaClock)
    {
        for (auto const &entity : _entities) {
            auto &spriteComponent = scene.GetComponent<SpriteComponent>(entity);

            // if (spriteComponent.isActive) {
            auto &tComp = scene.GetComponent<TransformComponent>(entity);
            auto &vComp = scene.GetComponent<VelocityComponent>(entity);

            auto time        = deltaClock.GetElapsedTimeAsSeconds();
            tComp.position.x = tComp.position.x + (vComp.velocity.x * time);
            tComp.position.y = tComp.position.y + (vComp.velocity.y * time);

            spriteComponent.sprite.SetPosition({ (tComp.position.x), (tComp.position.y) });
            // }
        }
    }
};
