/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Audio
*/

#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>

namespace nuts
{
    enum AudioStatus
    {
        Stopped,
        Paused,
        Playing
    };

    class SoundBuffer
    {
        private:
            sf::SoundBuffer _sound_buffer;

        public:
            SoundBuffer()
            {

            };

            ~SoundBuffer()
            {

            };

            bool LoadFromFile(const std::string &path)
            {
                return (_sound_buffer.loadFromFile(path));
            }

            const sf::SoundBuffer &GetSoundBuffer()
            {
                return (_sound_buffer);
            }
    };

    class Sound
    {
        private:
            sf::Sound _sound;

        public:
            Sound() {
                // std::cout << "Sound class created" << std::endl;
            };

            ~Sound() {
                // std::cout << "Sound class destroyed" << std::endl;
            };

            Sound(nuts::SoundBuffer &buf) {
                _sound.setBuffer(buf.GetSoundBuffer());
            };

            void Play()
            {
                // std::cout << "Playing sound" << std::endl;
                _sound.play();
            }

            void Pause()
            {
                _sound.pause();
            }

            void Stop()
            {
                _sound.stop();
            }

            void SetSoundBuffer(const sf::SoundBuffer &buf)
            {
                // std::cout << "Setting buffer" << std::endl;
                _sound.setBuffer(buf);
            }

            void SetVolume(const float volume)
            {
                _sound.setVolume(volume);
            }

            void SetPitch(const float pitch)
            {
                _sound.setPitch(pitch);
            }

            const sf::SoundBuffer *GetBufferFromSound()
            {
                return (_sound.getBuffer());
            }
    };

    class Music
    {
        private:
            sf::Music _music;

        public:
            Music() {};

            Music(const std::string &path)
            {
                if (!_music.openFromFile(path)) {
                    std::cout << "Error loading music file" << std::endl;
                }
            }

            bool OpenFromFile(const std::string &path)
            {
                return (_music.openFromFile(path));
            }

            ~Music()
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
}