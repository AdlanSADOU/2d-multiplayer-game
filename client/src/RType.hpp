/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RType
*/

#pragma once

#include "Nuts/Engine.hpp"
#include "Nuts/Audio.hpp"

#include "Nuts/EcsCore/Scene.hpp"

#include "Nuts/Clock.hpp"

#include "Nuts/EcsComponents/SpriteComponent.hpp"
#include "Nuts/EcsComponents/TransformComponent.hpp"
#include "Nuts/EcsComponents/VelocityComponent.hpp"
#include "Nuts/EcsComponents/SoundComponent.hpp"

#include "Nuts/EcsSystems/AnimationSystem.hpp"
#include "Nuts/EcsSystems/RenderSystem.hpp"
#include "Nuts/EcsSystems/TransformSystem.hpp"
#include "Nuts/EcsSystems/SoundSystem.hpp"

#include "Nuts/Networking.hpp"

#include "RTypeMenu.hpp"

// #include "engine/Nuts/GameObject.hpp"

class RTypeMonster : public nuts::GameObject
{
    private:
        nuts::Texture _texture;
        nuts::SoundBuffer _buffer;

    public:
        RTypeMonster() {};
        ~RTypeMonster() {};

        void Init()
        {
            this->Create("Monster");
            _texture.LoadFromFile("./resources/sprites/r-typesheet3.gif");
            _buffer.LoadFromFile("./resources/sounds/explosion.wav");

            this->AddComponent<TransformComponent>();
            this->AddComponent<SpriteComponent>();
            this->AddComponent<VelocityComponent>();
            this->AddComponent<SoundComponent>();

            TransformComponent &transformComponent = GetComponent<TransformComponent>();
            SpriteComponent &spriteComponent = GetComponent<SpriteComponent>();
            SoundComponent &soundComponent = GetComponent<SoundComponent>();

            spriteComponent.sprite.SetTexture(_texture);
            spriteComponent.sprite.SetTextureRect({ 0, 0, 16, 14 });
            spriteComponent.sprite.SetAnimated(true);
            spriteComponent.sprite.SetLooped(true);
            spriteComponent.sprite.SetFirstFrame({ 0, 0, 16, 14 });
            spriteComponent.sprite.SetFrameCount(12);
            spriteComponent.sprite.SetFrameTime(0.000005);

            transformComponent.position = { 0, 0 };

            soundComponent.sound.SetSoundBuffer(_buffer.GetSoundBuffer());
            soundComponent.sound.Play();
        }
};

class RType : public Net::INetClient
{
    enum game_state {
        MENU,
        GAME
    };

    public:
        RType();
        ~RType();

        void Init();
        void Run();

        void OnNetReceivedId(Event &event);
        void OnLobbyScreenBtn(Event &event);

    protected:
    private:
        RTypeMenu _menu;

        // TEST A SUPPRIMER APRES
        RTypeMonster _monster;
        //

        nuts::Clock _deltaClock;

        std::shared_ptr<nuts::Engine> _engine;

        std::shared_ptr<RenderSystem>    _renderSystem;
        std::shared_ptr<TransformSystem> _transformSystem;
        std::shared_ptr<AnimationSystem> _animationSystem;
        std::shared_ptr<SoundSystem>     _soundSystem;
};
