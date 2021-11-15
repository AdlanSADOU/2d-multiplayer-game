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
    _engine = std::make_shared<nuts::Engine>();

    _engine->InitWindow("R-Type", 800, 600);
    _engine->SetFramerateLimit(60);

    scene.Init();
    scene.RegisterComponent<TransformComponent>();
    scene.RegisterComponent<SpriteComponent>();
    scene.RegisterComponent<VelocityComponent>();
    scene.RegisterComponent<WidgetComponent>();

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
    scene.AddEventCallback(Net::Events::NEW_CLIENT, BIND_CALLBACK(&RType::OnNewClient, this));
    scene.AddEventCallback(Net::Events::CLIENT_QUIT, BIND_CALLBACK(&RType::OnClientQuit, this));
    scene.AddEventCallback(Net::Events::INITIAL_GAME_INFO, BIND_CALLBACK(&RType::OnInitialGameInfo, this));

    scene.AddEventCallback(Events::Btn::BTN_LOBBY_SCREEN, BIND_CALLBACK(&RType::OnQuickPlayBtn, this));

    _menu.Init(_engine);
}

void RType::Run()
{
    while (_engine->IsRunning()) {
        _engine->Clear();
        _engine->HandleEvent();

        if (_engine->IsKeyPressed(nuts::Key::LeftArrow)) {
            scene.InvokeEvent(nuts::Key::LeftArrow);
        }

        if (_engine->IsKeyPressed(nuts::Key::P)) {
            sf::Packet packet;
            packet << Net::Events::CLIENTS_PRINT;
            INetClient::TcpSend(packet);
        }

        _transformSystem.get()->Update(_deltaClock);
        _animationSystem.get()->Update(_deltaClock);
        _renderSystem.get()->Update(_engine->window);

        INetClient::Update();
        _menu._widgetMenu.logo.TEST_DRAW(_engine->window);
        _menu._widgetMenu.panel.TEST_DRAW(_engine->window);
        _menu._widgetMenu.btnLobby.TEST_DRAW(_engine->window);

        if (_menu._widgetMenu.btnLobby.IsHovered(_engine->GetMousePos())
            && _engine->IsMouseBtnPressed(nuts::Button::Left)) {
            _menu._widgetMenu.btnLobby.InvokeEvent(Event(Events::Btn::BTN_LOBBY_SCREEN));

        }

        _engine->Present();
        _deltaClock.Restart();
    }
}
