/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RType
*/

#include "RType.hpp"

#include "Nuts/Input.hpp"

RType::RType()
{
}

RType::~RType()
{
}

void RType::Init()
{
    _engine.InitWindow("R-Type", 800, 600);
    _engine.SetFramerateLimit(60);

    scene.Init();
    scene.RegisterComponent<TransformComponent>();
    scene.RegisterComponent<SpriteComponent>();
    scene.RegisterComponent<VelocityComponent>();

    _renderSystem    = scene.RegisterSystem<RenderSystem>();
    _transformSystem = scene.RegisterSystem<TransformSystem>();
    _animationSystem = scene.RegisterSystem<AnimationSystem>();

    EntitySignature transformSig;
    transformSig.set(scene.GetComponentType<TransformComponent>());
    transformSig.set(scene.GetComponentType<VelocityComponent>());
    scene.SetSystemSignature<TransformSystem>(transformSig);

    EntitySignature renderSig;
    renderSig.set(scene.GetComponentType<SpriteComponent>());
    scene.SetSystemSignature<RenderSystem>(renderSig);

    EntitySignature animationSig;
    animationSig.set(scene.GetComponentType<SpriteComponent>());
    scene.SetSystemSignature<AnimationSystem>(animationSig);

    _transformSystem->Init();
    _monster.Init();
    _deltaClock.Restart();

    scene.AddEventCallback(Net::Events::CLIENT_ID, BIND_CALLBACK(&RType::OnNetReceivedId, this));

    INetClient::Connect(sf::IpAddress::getLocalAddress(), 55001);
}

void RType::Run()
{
    while (_engine.IsRunning()) {
        _engine.Clear();
        _engine.HandleEvent();

        if (_engine.GetKeyPressed(nuts::Key::Left)) {
            scene.InvokeEvent(nuts::Key::Left);
        }

        if (_engine.GetKeyPressed(nuts::Key::P)) {
            sf::Packet packet;
            packet << Net::Events::CLIENTS_PRINT;
            INetClient::TcpSend(packet);
        }

        _transformSystem.get()->Update(_deltaClock);
        _animationSystem.get()->Update(_deltaClock);
        _renderSystem.get()->Update(_engine.window);

        INetClient::Update();

        _engine.Present();
        _deltaClock.Restart();
    }
}