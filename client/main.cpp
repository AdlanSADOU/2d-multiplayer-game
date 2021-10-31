/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>

#include <Nuts.h>

#include <EscCore/Scene.h>
#include <EscSystems/RenderSystem.h>

#include <iostream>
#include <bitset>
#include <cassert>

Scene gScene;

int main()
{

    Nuts nuts;
    nuts.InitWindow("R-TYPE", 700, 200);

    /**
     * Scene is a global instance holding references to all managers:
     * ComponentManager
     * EntityManager
     * SystemManager
     * EventManager --> unsused for now, maybe we'll trash it
     *
     * The scene knows about every entity, components and systems
     * and manages communication between them
     **/
    gScene.Init();
    gScene.RegisterComponent<TransformComponent>();
    gScene.RegisterComponent<SpriteComponent>();

    ///////////////////////////
    // RenderSystem
    auto renderSystem = gScene.RegisterSystem<RenderSystem>();
    {
        EntitySignature sig;
        sig.set(gScene.GetComponentType<TransformComponent>());
        sig.set(gScene.GetComponentType<SpriteComponent>());
        gScene.SetSystemSignature<RenderSystem>(sig);
    }

    ///////////////////////////
    // Entity
    Entity playerEntity;
    playerEntity = gScene.CreateEntity();
    gScene.AddComponent(playerEntity, TransformComponent{});
    gScene.AddComponent(playerEntity, SpriteComponent{});

    TransformComponent &playerTransformComponent = gScene.GetComponent<TransformComponent>(playerEntity);
    SpriteComponent &playerSprite = gScene.GetComponent<SpriteComponent>(playerEntity);

    playerTransformComponent.position = {10, 10};
    playerSprite.texture.loadFromFile("resources/r_type_logo.png");
    playerSprite.sprite.setTexture(playerSprite.texture);
    playerSprite.sprite.setPosition(playerTransformComponent.position);

    // GameLoop
    while (nuts.IsRunning())
    {
        nuts.HandleInput();

        nuts.Clear();

        if (nuts.GetKeyPressed(sf::Keyboard::Q))
            printf("WORKING !!\n");

        renderSystem->Update(nuts.window); // iterates over and draws entities

        nuts.Present();
    }

    return 0;
}
