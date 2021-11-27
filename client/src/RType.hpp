/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RType
*/

#pragma once

#include "Nuts/Audio.hpp"
#include "Nuts/Engine.hpp"
#include "Nuts/UI/Text.hpp"

#include "Nuts/EcsCore/Scene.hpp"

#include "Nuts/Clock.hpp"

#include "Nuts/EcsComponents/SoundComponent.hpp"
#include "Nuts/EcsComponents/SpriteComponent.hpp"
#include "Nuts/EcsComponents/TransformComponent.hpp"
#include "Nuts/EcsComponents/VelocityComponent.hpp"
#include "Nuts/EcsComponents/StateComponent.hpp"

#include "Nuts/EcsSystems/AnimationSystem.hpp"
#include "Nuts/EcsSystems/RenderSystem.hpp"
#include "Nuts/EcsSystems/SoundSystem.hpp"
#include "Nuts/EcsSystems/TransformSystem.hpp"

#include "Nuts/Networking.hpp"

#include "RTypeGame.hpp"
#include "RTypeMatchmaking.hpp"
#include "RTypeMenu.hpp"

#include "RGameState.hpp"

// #include "engine/Nuts/GameObject.hpp"

class RType : public Net::INetClient
{

public:
    RType();
    ~RType();

    void Init();
    void Run();

    auto &GetGame() const
    {
        return _game;
    }

    void OnNetReceivedId(Event &event);
    void OnLobbyScreenBtn(Event &event);
    void OnBtnQuit(Event &event);

    void OnQuickPlayBtn(Event &event);
    void OnNewClient(Event &event);
    void OnClientQuit(Event &event);
    void OnStartGame(Event &event);

    std::thread *clientUpdateThread;

    GameState _state = GameState::MENU;

protected:
private:
    RTypeMenu        _menu;
    RTypeMatchmaking _matchMaking;

    std::shared_ptr<RTypeGame> _game;

    nuts::Clock _deltaClock;

    std::shared_ptr<nuts::Engine> _engine;

    std::shared_ptr<RenderSystem>    _renderSystem;
    std::shared_ptr<TransformSystem> _transformSystem;
    std::shared_ptr<AnimationSystem> _animationSystem;
    std::shared_ptr<SoundSystem>     _soundSystem;
};
