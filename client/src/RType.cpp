/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RType
*/

#include "RType.hpp"

#include <Nuts/Input.hpp>
#include <Nuts/Utilities.hpp>

#include <cstring>

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
    scene.RegisterComponent<StateComponent>();

    _renderSystem    = scene.RegisterSystem<RenderSystem>();
    _transformSystem = scene.RegisterSystem<TransformSystem>();
    _animationSystem = scene.RegisterSystem<AnimationSystem>();
    _soundSystem     = scene.RegisterSystem<SoundSystem>();

    EntitySignature transformSig;
    transformSig.set(scene.GetComponentType<TransformComponent>());
    transformSig.set(scene.GetComponentType<VelocityComponent>());
    transformSig.set(scene.GetComponentType<StateComponent>());
    scene.SetSystemSignature<TransformSystem>(transformSig);

    EntitySignature renderSig;
    renderSig.set(scene.GetComponentType<SpriteComponent>());
    renderSig.set(scene.GetComponentType<StateComponent>());
    scene.SetSystemSignature<RenderSystem>(renderSig);

    EntitySignature animationSig;
    animationSig.set(scene.GetComponentType<SpriteComponent>());
    animationSig.set(scene.GetComponentType<StateComponent>());
    scene.SetSystemSignature<AnimationSystem>(animationSig);

    EntitySignature soundSig;
    soundSig.set(scene.GetComponentType<SoundComponent>());
    scene.SetSystemSignature<SoundSystem>(soundSig);

    _soundSystem->Init();

    _transformSystem->Init();
    _deltaClock.Restart();

    _menu.Init(_engine);
    _matchMaking.Init(_engine);

    _game = std::make_shared<RTypeGame>();
    _game->Init(_engine);

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
        _engine->HandleEvent();

        _engine->Clear();

        if (_engine->IsKeyPressed(nuts::Key::P)) {
            sf::Packet packet;
            packet << (EventType)Net::Events::CLIENTS_PRINT;
            INetClient::TcpSend(packet);
        }

        _transformSystem->Update(_deltaClock, _state);
        _animationSystem->Update(_deltaClock, _state);
        _renderSystem->Update(_engine->window, _state);
        _soundSystem->Update();

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
                _menu._widgetMenu.btnLobby.GetText().TEST_DRAW(_engine->window);
                _menu._widgetMenu.btnQuit.TEST_DRAW(_engine->window);
                _menu._widgetMenu.btnQuit.GetText().TEST_DRAW(_engine->window);
                break;

            case GameState::MATCHM:
                _matchMaking.Draw();
                break;

            case GameState::GAME:

                if (GetLocalClientId() == -1) return;
                _game->Update();
                _game->Draw();

                // if (INetClient::GetAccumulatorTime().asSeconds() > 1 / (58.f))
                {
                    // INetClient::ResetAccumulatorTime();

                    GPlayer *localPlayer = (_game->GetLocalPlayer());
                    if (_game->isReady && localPlayer != nullptr) {

                        sf::Packet playerStatePacket;
                        playerStatePacket << Net::Events::CLIENT_UPDATE_PACKETS
                                          << GetLocalClientId()
                                          << localPlayer->_directionalKeys[0]
                                          << localPlayer->_directionalKeys[1]
                                          << localPlayer->_directionalKeys[2]
                                          << localPlayer->_directionalKeys[3]
                                          << localPlayer->GetPosition().x
                                          << localPlayer->GetPosition().y
                                          << localPlayer->IsFiering()
                                          << _game->_destroyed_monster_id;
                        // COUT(
                        //     GetLocalClientId()
                        //     << localPlayer->_directionalKeys[0]
                        //     << localPlayer->_directionalKeys[1]
                        //     << localPlayer->_directionalKeys[2]
                        //     << localPlayer->_directionalKeys[3]
                        //     << localPlayer->GetPosition().x
                        //     << localPlayer->GetPosition().y
                        //     << localPlayer->IsFiering()
                        //     << _game->_destroyed_monster_id << "\n");

                        if (_game->_destroyed_monster_id != -1)
                            COUT("[UDP-SEND]: destroyed monster with id: " << _game->_destroyed_monster_id << "\n");

                        INetClient::UdpSend(playerStatePacket);
                    }
                }

                break;

            default:
                break;
        }
        _deltaClock.Restart();
        _engine->Present();

    }
}
