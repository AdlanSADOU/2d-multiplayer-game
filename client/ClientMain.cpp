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
#include <GameObject.hpp>

#include <bitset>
#include <cassert>

Scene gScene;
ClientID myID;

int main()
{
    sf::IpAddress serverIp = sf::IpAddress::LocalHost;
    sf::Uint16 serverPort = 55001;

    sf::TcpSocket tcpSock;
    sf::UdpSocket udpSock;

    bool isConnected = false;
    tcpSock.setBlocking(false);
    udpSock.setBlocking(false);

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

    // // Entity
    // Entity playerEntity;
    // playerEntity = gScene.CreateEntity();
    // gScene.AddComponent(playerEntity, TransformComponent {});
    // gScene.AddComponent(playerEntity, SpriteComponent {});

    // TransformComponent& playerTransformComponent = gScene.GetComponent<TransformComponent>(playerEntity);
    // SpriteComponent& playerSprite = gScene.GetComponent<SpriteComponent>(playerEntity);

    // playerTransformComponent.position = { 10, 10 };
    // playerSprite.texture.loadFromFile("resources/r_type_logo.png");
    // playerSprite.sprite.setTexture(playerSprite.texture);
    // playerSprite.sprite.setPosition(playerTransformComponent.position);

    // GameObject example

    GameObject logo = GameObject("logo");
    logo.AddComponent<TransformComponent>();
    logo.AddComponent<SpriteComponent>();

    TransformComponent& logoTrans = logo.GetComponent<TransformComponent>();
    SpriteComponent& logoSprite = logo.GetComponent<SpriteComponent>();

    logoTrans.position = { 10, 10 };
    logoSprite.texture.loadFromFile("resources/r_type_logo.png");
    logoSprite.sprite.setTexture(logoSprite.texture);
    logoSprite.sprite.setPosition(logoTrans.position);

    // GameLoop
    while (nuts.IsRunning()) {
        nuts.HandleEvent();

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
            sock_status = tcpSock.connect(serverIp, serverPort);
            if (sock_status == sf::Socket::Error)
                printf("Error: connection timed out\n");

            udpSock.bind(sf::Socket::AnyPort);

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
                if (tcpSock.send(packet) == sf::Socket::Status::Done) {
                    isConnected = false;
                    tcpSock.disconnect();
                }
            }
        }

        if (nuts.GetKeyPressed(Input::Key::P)) {
            sf::Packet packet;
            printf("[CLIENT]: print clients request\n");
            packet << RPC(ERpc::CLIENTS_PRINT) << myID;
            // if (packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize)
            if (isConnected)
                udpSock.send(packet, serverIp, serverPort + 1);
        }

        { // TCP Receive loop
            sf::Packet packet;
            Rpc rpcType = -1;

            sf::Socket::Status status = tcpSock.receive(packet);
            if (status == sf::Socket::Done)
                packet >> rpcType >> myID;

            switch (rpcType)
            {
                case RPC(ERpc::CLIENT_CONNECT): {
                    printf("[Client]: connected to server with ID:[%d]\n", myID);

                    sf::Packet udpConnect;
                    udpConnect << RPC(ERpc::CLIENT_UDP) << myID << udpSock.getLocalPort();
                    udpSock.send(udpConnect, serverIp, serverPort + 1);

                } break;

                default:
                    break;
            }
        }

        if (isConnected) { // UDP Receive loop
            sf::Packet packet;
            Rpc rpcType = -1;

            sf::IpAddress remoteAddress;
            unsigned short remotePort;

            sf::Socket::Status status = udpSock.receive(packet, remoteAddress, remotePort);
            if (status == sf::Socket::Done) {
                packet >> rpcType >> myID;
                printf("[Client]: received UPD packet:[%d]\n", myID, rpcType);
            }

            switch (rpcType)
            {
                case RPC(ERpc::CLIENT_UDP) : {
                    printf("[Client]: server regisreted UDP info\n", myID);
                } break;

                default:
                    break;
            }
        }

        renderSystem->Update(nuts.window); // iterates over and draws entities

        nuts.Present();
    }

    return 0;
}
