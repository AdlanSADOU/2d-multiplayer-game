/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <Nuts.h>
#include <Nuts/Networking.h>

#include <EcsCore/Scene.h>
#include <EcsSystems/RenderSystem.h>

#include <iostream>
#include <bitset>
#include <cassert>

static Scene gScene;
static ClientID myID;

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

		sf::Socket::Status sock_status;

		/** Establish first connection
		 * Client is not registered to server at this point
		 */
		if (nuts.GetKeyPressed(sf::Keyboard::Num1))
		{
			sock_status = tcpSock.connect(sf::IpAddress::LocalHost, 55001);
			if (sock_status == sf::Socket::Error)
				printf("Error: connection timed out\n");
			isConnected = true;
			printf("connected to server\n");
		}

		/**
		 * Ask server to be registered on it and receive ClientID
		 * used for any further communication
		 */
		if (nuts.GetKeyPressed(sf::Keyboard::Num2))
		{
			if (isConnected)
			{
				printf("[Client]: connection request\n");
				sf::Packet packet;
				packet << ERpc::CLIENT_CONNECT;

				tcpSock.send(packet);
			}
		}

		/**
		* Disconnect client
		*/
		if (nuts.GetKeyPressed(sf::Keyboard::Num0))
		{
			if (isConnected)
			{
				printf("[Client]: disconnection request\n");
				sf::Packet packet;
				packet << ERpc::CLIENT_DISCONNECT << myID;

				tcpSock.send(packet);
			}
		}

		sf::Packet packet;
		Rpc rpcType = -1;

		sf::Socket::Status status = tcpSock.receive(packet);
		if (status == sf::Socket::Done)
		{
			packet >> rpcType;
			switch (rpcType)
			{
			case ERpc::CLIENT_CONNECT:
			{
				packet >> myID;
				printf("myID:[%d]", myID);
				break;
			}

			default:
				break;
			}
		}

		renderSystem->Update(nuts.window); // iterates over and draws entities

		nuts.Present();
	}

	return 0;
}
