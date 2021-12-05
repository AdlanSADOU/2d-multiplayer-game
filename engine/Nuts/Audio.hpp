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

namespace nuts {
    /**
     * @brief Status of the sound.
     * Corresponding to the audio state, is set to Playing if the sound is currently playing, to Paused if the sound is paused, and to Stopped if the sound is stopped.
     */
    enum AudioStatus
    {
        Stopped,
        Paused,
        Playing
    };

    /**
     * @brief Storage for audio samples defining a sound.
     *
     */
    class SoundBuffer {
    private:
        sf::SoundBuffer _sound_buffer;

    public:
        /**
         * @brief Construct a new Sound Buffer object
         *
         */
        SoundBuffer()
        {
            std::cout << "Sound buffer created" << std::endl;
        };

        SoundBuffer(const std::string &path)
        {
            _sound_buffer.loadFromFile(path);
        };

        /**
         * @brief Destroy the Sound Buffer object
         *
         */
        ~SoundBuffer()
        {
            std::cout << "Sound buffer destroyed" << std::endl;
        };

        /**
         * @brief Load the sound buffer from a file.
         *
         * @param path Path of the sound file to load
         * @return True if loading suceeded, false if it failed
         */
        bool LoadFromFile(const std::string &path)
        {
            return (_sound_buffer.loadFromFile(path));
        }

        /**
         * @brief Get the sound buffer at its current state
         *
         * @return const sf::SoundBuffer&
         */
        const sf::SoundBuffer &GetSoundBuffer()
        {
            return (_sound_buffer);
        }
    };

    /**
     * @brief Regular sound that can be played in the audio environment
     *
     */
    class Sound {
    private:
        sf::Sound        *_sound = nullptr;
        sf::Sound::Status _status;

    public:
        /**
         * @brief Construct a new Sound object
         *
         */
        Sound() {
            // std::cout << "Sound class created" << std::endl;
        };

        /**
         * @brief Destroy the Sound object
         *
         */
        ~Sound() {
            // std::cout << "Sound class destroyed" << std::endl;
        };

        /**
         * @brief Construct a new Sound object with a buffer
         *
         * @param buf buffer containing the audio data to play with the sound
         */
        Sound(nuts::SoundBuffer &buf)
        {
            _sound = new sf::Sound();
            _sound->setBuffer(buf.GetSoundBuffer());
        };

        /**
         * @brief Start or resume playing the sound
         * This function starts the stream if it was stopped, resumes it if it was paused, and restarts it from beginning if it was it already playing. This function uses its own thread so that it doesn't block the rest of the program while the sound is played.
         */
        void Play()
        {
            // std::cout << "Playing sound" << std::endl;
            _sound->play();
        }

        /**
         * @brief Pause the sound
         * This function pauses the sound if it was playing, otherwise (sound already paused or stopped) it has no effect.
         */
        void Pause()
        {
            _sound->pause();
        }

        /**
         * @brief Stop playing the sound
         * This function stops the sound if it was playing or paused, and does nothing if it was already stopped. It also resets the playing position (unlike pause()).
         */
        void Stop()
        {
            _sound->stop();
        }

        bool IsPlaying()
        {
            bool mabool = false;

            if (_sound->getStatus() == sf::Sound::Playing)
                mabool = true;
            return mabool;
        }

        /**
         * @brief Set the source buffer containing the audio data to play.
         *
         * @param buf buffer to attach to the sound
         */
        void SetSoundBuffer(const sf::SoundBuffer &buf)
        {
            _sound = new sf::Sound();
            _sound->setBuffer(buf);
        }

        /**
         * @brief Set the volume of the sound.
         *
         * @param volume Volume of the sound
         */
        void SetVolume(const float volume)
        {
            _sound->setVolume(volume);
        }

        /**
         * @brief Set the pitch of the sound.
         * The pitch represents the perceived fundamental frequency of a sound; thus you can make a sound more acute or grave by changing its pitch. A side effect of changing the pitch is to modify the playing speed of the sound as well. The default value for the pitch is 1.
         * @param pitch New pitch to apply to the sound
         */
        void SetPitch(const float pitch)
        {
            _sound->setPitch(pitch);
        }

        /**
         * @brief Get the audio buffer attached to the sound.
         *
         * @return const sf::SoundBuffer* Buffer attached to the sound (can be NULL)
         */
        const sf::SoundBuffer *GetBufferFromSound()
        {
            return (_sound->getBuffer());
        }
    };

    /**
     * @brief Streamed Music played from an audi file
     *
     */
    class Music {
    private:
        sf::Music _music;

    public:
        /**
         * @brief Construct a new Music object
         * The music object will be null.
         * To load directly the music from a file, use the other constructor instead.
         */
        Music() {};

        /**
         * @brief Construct a new Music object
         * with a specified audio file
         * @param path Path to the music file to open
         */
        Music(const std::string &path)
        {
            if (!_music.openFromFile(path)) {
                std::cout << "Error loading music file" << std::endl;
            }
        }

        /**
         * @brief Open a music from an audio file.
         * his function doesn't start playing the music (call play() to do so). See the documentation of sf::InputSoundFile for the list of supported formats.
         * @param path Path of the music file to open
         * @return true
         * @return false
         */
        bool OpenFromFile(const std::string &path)
        {
            return (_music.openFromFile(path));
        }

        /**
         * @brief Destroy the Music object
         *
         */
        ~Music()
        {
            _music.~Music();
        }

        /**
         * @brief Start or resume playing the audio stream.
         * This function starts the stream if it was stopped, resumes it if it was paused, and restarts it from the beginning if it was already playing. This function uses its own thread so that it doesn't block the rest of the program while the stream is played.
         */
        void Play()
        {
            _music.play();
        }

        /**
         * @brief Stops playing the audio stream
         *
         */
        void Stop()
        {
            _music.stop();
        }

        /**
         * @brief Pause the audio stream.
         * This function pauses the stream if it was playing, otherwise (stream already paused or stopped) it has no effect.
         */
        void Pause()
        {
            _music.pause();
        }

        /**
         * @brief Set the Volume of the sound
         * The volume is a value between 0 (mute) and 100 (full volume). The default value for the volume is 100.
         * @param volume Volume of the sound
         */
        void SetVolume(float volume)
        {
            _music.setVolume(volume);
        }

        /**
         * @brief Set whether or not the stream should loop after reaching the end.
         * If set, the stream will restart from beginning after reaching the end and so on, until it is stopped or setLoop(false) is called. The default looping state for streams is false.
         * @param loop True to play in loop, false to play once
         */
        void SetLoop(bool loop)
        {
            _music.setLoop(loop);
        }

        /**
         * @brief Set the Pitch of the sound
         * The pitch represents the perceived fundamental frequency of a sound; thus you can make a sound more acute or grave by changing its pitch. A side effect of changing the pitch is to modify the playing speed of the sound as well. The default value for the pitch is 1.
         * @param pitch New pitch to apply to the sound
         */
        void SetPitch(float pitch)
        {
            _music.setPitch(pitch);
        }
    };
}