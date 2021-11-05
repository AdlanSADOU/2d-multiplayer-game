/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>

#include <Nuts.hpp>
#include <Nuts/Input.hpp>
#include <Nuts/Networking.hpp>

#include <EcsCore/Scene.hpp>
#include <EcsSystems/RenderSystem.hpp>

#include <bitset>
#include <cassert>

Scene gScene;
ClientID myID;

int main()
{
    sf::TcpSocket tcpSock;
    bool isConnected = false;
    tcpSock.setBlocking(false);

    Nuts nuts;
    nuts.InitWindow("R-TYPE", 700, 200);

    /**
	 * Scene is a global instance holding references to all managers:
	 * ComponentManager
	 * EntityManager
	 * SystemManager
	 *
	 * The scene knows about every entity, components and systems
	 * and manages communication between them
	 **/
    gScene.Init();
    gScene.RegisterComponent<TransformComponent>();
    gScene.RegisterComponent<SpriteComponent>();

    // RenderSystem
    auto renderSystem = gScene.RegisterSystem<RenderSystem>();
    {
        EntitySignature sig;
        sig.set(gScene.GetComponentType<TransformComponent>());
        sig.set(gScene.GetComponentType<SpriteComponent>());
        gScene.SetSystemSignature<RenderSystem>(sig);
    }

    // Entity
    Entity playerEntity;
    playerEntity = gScene.CreateEntity();
    gScene.AddComponent(playerEntity, TransformComponent {});
    gScene.AddComponent(playerEntity, SpriteComponent {});

    TransformComponent& playerTransformComponent = gScene.GetComponent<TransformComponent>(playerEntity);
    SpriteComponent& playerSprite = gScene.GetComponent<SpriteComponent>(playerEntity);

    playerTransformComponent.position = { 10, 10 };
    playerSprite.texture.loadFromFile("resources/r_type_logo.png");
    playerSprite.sprite.setTexture(playerSprite.texture);
    playerSprite.sprite.setPosition(playerTransformComponent.position);

    // GameLoop
    while (nuts.IsRunning()) {
        nuts.HandleInput();

        nuts.Clear();

        sf::Socket::Status sock_status;

        /** Establish first connection
		 * Client is not connected to server at this point
		 */
        if (nuts.GetKeyPressed(Input::Key::Num1)) {
            printf("[Client]: connection request\n");

            if (isConnected) {
                printf("[Client]: Already connected with ID:[%d]\n", myID);
                continue;
            }
            sock_status = tcpSock.connect(sf::IpAddress::LocalHost, 55001);
            if (sock_status == sf::Socket::Error)
                printf("Error: connection timed out\n");

            isConnected = true;
        }

        /**
		* Disconnect client
		*/
        if (nuts.GetKeyPressed(Input::Key::Num0)) {
            if (isConnected) {
                printf("[CLIENT]: disconnection request\n");

                sf::Packet packet;
                packet << RPC(ERpc::CLIENT_DISCONNECT) << myID;
                if (tcpSock.send(packet) == sf::Socket::Status::Done)
                    ;
                {
                    isConnected = false;
                    tcpSock.disconnect();
                }
            }
        }

        if (nuts.GetKeyPressed(Input::Key::P)) {
            sf::Packet packet;
            printf("[CLIENT]: print clients request\n");
            packet << RPC(ERpc::CLIENTS_PRINT);
            tcpSock.send(packet);
        }

        sf::Packet packet;
        Rpc rpcType = -1;

        sf::Socket::Status status = tcpSock.receive(packet);
        if (status == sf::Socket::Done)
            packet >> static_cast<sf::Uint8>(rpcType) >> myID;

        switch (rpcType) {
        case ERpc::CLIENT_CONNECT: {
            if (packet >> myID)
                ;
            printf("[Client]: connected to server with ID:[%d]\n", myID);
        } break;

        default:
            break;
        }

        renderSystem->Update(nuts.window); // iterates over and draws entities

        nuts.Present();
    }

    return 0;
}
