/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RType
*/

#pragma once

#include "Nuts/Engine.hpp"

#include "Nuts/EcsCore/Scene.hpp"

#include "Nuts/Networking.hpp"

#include "Nuts/EcsComponents/SpriteComponent.hpp"
#include "Nuts/EcsComponents/TransformComponent.hpp"
#include "Nuts/EcsComponents/VelocityComponent.hpp"

#include "Nuts/EcsSystems/RenderSystem.hpp"
#include "Nuts/EcsSystems/TransformSystem.hpp"

class RType {

    enum game_state {
        MENU,
        GAME
    };

    public:
        RType();
        ~RType();

        void Init();
        void Run();

    protected:
    private:
        Engine _nuts;

        std::shared_ptr<RenderSystem> _renderSystem;
        std::shared_ptr<TransformSystem> _transformSystem;
};
