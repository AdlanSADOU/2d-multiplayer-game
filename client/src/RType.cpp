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
    scene.RegisterComponent<SoundComponent>();

    _renderSystem    = scene.RegisterSystem<RenderSystem>();
    _transformSystem = scene.RegisterSystem<TransformSystem>();
    _animationSystem = scene.RegisterSystem<AnimationSystem>();
    _soundSystem     = scene.RegisterSystem<SoundSystem>();

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

    EntitySignature soundSig;
    soundSig.set(scene.GetComponentType<SoundComponent>());
    scene.SetSystemSignature<SoundSystem>(soundSig);

    _monster.Init();
    _soundSystem->Init();

    _transformSystem->Init();
    _deltaClock.Restart();

    _menu.Init(_engine);
    _matchMaking.Init(_engine);
    _game.Init(_engine);

    scene.AddEventCallback(Net::Events::CLIENT_ID, BIND_CALLBACK(&RType::OnNetReceivedId, this));
    scene.AddEventCallback(Net::Events::NEW_CLIENT, BIND_CALLBACK(&RType::OnNewClient, this));
    scene.AddEventCallback(Net::Events::CLIENT_QUIT, BIND_CALLBACK(&RType::OnClientQuit, this));
    scene.AddEventCallback(Net::Events::GAME_START, BIND_CALLBACK(&RType::OnStartGame, this));

    scene.AddEventCallback(Events::Btn::BTN_LOBBY_SCREEN, BIND_CALLBACK(&RType::OnQuickPlayBtn, this));
    scene.AddEventCallback(Events::Btn::BTN_QUIT, BIND_CALLBACK(&RType::OnBtnQuit, this));
}

void RType::OnBtnQuit(Event &event)
{
    _engine->CloseWindow();
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

        switch (_state) {
            case GameState::MENU:
                if (_menu._widgetMenu.btnLobby.IsHovered(_engine->GetMousePos())
                    && _engine->IsMouseBtnPressed(nuts::Button::Left)) {
                    _menu._widgetMenu.btnLobby.InvokeEvent(Event(Events::Btn::BTN_LOBBY_SCREEN));
                }

                if (_menu._widgetMenu.btnQuit.IsHovered(_engine->GetMousePos())
                    && _engine->IsMouseBtnPressed(nuts::Button::Left)) {
                    _menu._widgetMenu.btnQuit.InvokeEvent(Event(Events::Btn::BTN_QUIT));
                }

                _menu._widgetMenu.logo.TEST_DRAW(_engine->window);
                _menu._widgetMenu.panel.TEST_DRAW(_engine->window);
                _menu._widgetMenu.btnLobby.TEST_DRAW(_engine->window);
                _menu._widgetMenu.btnLobby.GetText().Draw(_engine->window);
                _menu._widgetMenu.btnQuit.TEST_DRAW(_engine->window);
                _menu._widgetMenu.btnQuit.GetText().Draw(_engine->window);
                break;

            case GameState::MATCHM:
                _matchMaking.Draw();
                break;

            case GameState::GAME:

                // if (_engine->IskeyEvent())

                if (INetClient::GetAccumulatorTime().asSeconds() > 1 / 33.f) {
                    INetClient::ResetAccumulatorTime();

                    nuts::Key key = nuts::Unknown;

                    if (_engine->IsKeyPressed(nuts::Key::A))
                        key = nuts::A;
                    else if (_engine->IsKeyPressed(nuts::Key::D))
                        key = nuts::D;
                    else if (_engine->IsKeyPressed(nuts::Key::W))
                        key = nuts::W;
                    else if (_engine->IsKeyPressed(nuts::Key::S))
                        key = nuts::S;

                    sf::Packet keyPacket;
                    keyPacket << Net::Events::CLIENT_KEY << GetLocalClientId() << key;
                    INetClient::UdpSend(keyPacket);
                }

                if (GetLocalClientId() == -1) return;
                _game.Update();
                _game.Draw();
                break;

            default:
                break;
        }
        _deltaClock.Restart();

        _engine->Present();
    }
}
