
#include <SFML/Graphics.hpp>

#include <Nuts.h>

#include <EscCore/Coordinator.h>
#include <EscSystems/RenderSystem.h>

#include <iostream>
#include <bitset>
#include <cassert>

Coordinator gCoordinator;

int main()
{

    Nuts nuts;
    nuts.InitWindow("test window", 400, 200);

    gCoordinator.Init();
    gCoordinator.RegisterComponent<TransformComponent>();
    gCoordinator.RegisterComponent<SpriteComponent>();

    auto renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
    {
        Signature sig;
        sig.set(gCoordinator.GetComponentType<TransformComponent>());
        sig.set(gCoordinator.GetComponentType<SpriteComponent>());
        gCoordinator.SetSystemSignature<RenderSystem>(sig);
    }


    Entity playerEntity;
    playerEntity = gCoordinator.CreateEntity();
    gCoordinator.AddComponent(playerEntity, TransformComponent{});
    gCoordinator.AddComponent(playerEntity, SpriteComponent{});

    TransformComponent &playerTransformComponent = gCoordinator.GetComponent<TransformComponent>(playerEntity);
    SpriteComponent &playerSprite = gCoordinator.GetComponent<SpriteComponent>(playerEntity);

    playerTransformComponent.position = {100,100};
    playerSprite.texture.loadFromFile("resources/me.jpg");
    playerSprite.sprite.setTexture(playerSprite.texture);
    playerSprite.sprite.setPosition(playerTransformComponent.position);

    while (nuts.IsRunning())
    {
        nuts.HandleInput();

        nuts.Clear();

        if (nuts.GetKeyPressed(sf::Keyboard::Q))
            printf("WORKING !!\n");

        renderSystem->Update(nuts.window);

        nuts.Present();
    }

    return 0;
}
