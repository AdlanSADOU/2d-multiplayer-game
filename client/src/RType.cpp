/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RType
*/

#include "RType.hpp"

RType::RType()
{

}

RType::~RType()
{

}

void RType::Init()
{
    _nuts.InitWindow("R-Type", 800, 600);
    _nuts.SetFramerateLimit(60);

    scene.Init();
    scene.RegisterComponent<TransformComponent>();
    scene.RegisterComponent<SpriteComponent>();
    scene.RegisterComponent<VelocityComponent>();

    _renderSystem = scene.RegisterSystem<RenderSystem>();
    _transformSystem = scene.RegisterSystem<TransformSystem>();

    EntitySignature transformSig;
    transformSig.set(scene.GetComponentType<TransformComponent>());
    transformSig.set(scene.GetComponentType<VelocityComponent>());
    scene.SetSystemSignature<TransformSystem>(transformSig);

    EntitySignature renderSig;
    renderSig.set(scene.GetComponentType<SpriteComponent>());
    scene.SetSystemSignature<RenderSystem>(renderSig);
}

void RType::Run()
{
    while (_nuts.IsRunning()) {
        _nuts.Clear();
        _nuts.HandleEvent();

        

        _transformSystem.get()->Update();
        _renderSystem.get()->Update(_nuts.window);

        _nuts.Present();
    }
}