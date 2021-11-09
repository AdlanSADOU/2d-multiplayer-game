/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Audio
*/

#pragma once

#include <SFML/Audio.hpp>

#include <iostream>

namespace NutsAudio
{
    class Music
    {
        private:
            sf::Music _music;

        public:
            Music::Music(const std::string &path)
            {
                if (!_music.openFromFile(path)) {
                    std::cout << "Error loading music file" << std::endl;
                }
            }

            Music::~Music()
            {
                _music.~Music();
            }

            void Play()
            {
                _music.play();
            }

            void Stop()
            {
                _music.stop();
            }

            void Pause()
            {
                _music.pause();
            }

            void SetVolume(float volume)
            {
                _music.setVolume(volume);
            }

            void SetLoop(bool loop)
            {
                _music.setLoop(loop);
            }

            void SetPitch(float pitch)
            {
                _music.setPitch(pitch);
            }
    };
} // namespace NutsAudio
