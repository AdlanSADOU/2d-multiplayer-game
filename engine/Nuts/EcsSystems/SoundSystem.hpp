/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SoundSystem
*/

#pragma once

#include "SoundComponent.hpp"

#include "System.hpp"
#include "Scene.hpp"

extern Scene scene;

class SoundSystem : public System
{
    private:

    public:
        void Init()
        {
            scene.AddEventCallback(nuts::Key::F, BIND_CALLBACK(&SoundSystem::PlaySound, this));
        }

        void PlaySound(Event &event)
        {
            
        }

        void Update()
        {
            for (auto const &entity : _entities)
            {
                auto &soundComponent = scene.GetComponent<SoundComponent>(entity);

                if (soundComponent.shouldPlay) {
                    soundComponent.sound.Play();
                    soundComponent.shouldPlay = false;
                }
            }
        }
};
