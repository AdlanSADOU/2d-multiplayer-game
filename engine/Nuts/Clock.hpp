/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Clock
*/

#pragma once

#include <SFML/System/Clock.hpp>

namespace nuts
{
    /**
     * @brief Utility class that mesures the elapsed time.
     * 
     */
    class Clock
    {
        private:
            sf::Clock _clock;

        public:
            /**
             * @brief Construct a new Clock object
             * 
             */
            Clock()
            {

            }

            /**
             * @brief Destroy the Clock object
             * 
             */
            ~Clock()
            {

            }

            /**
             * @brief Get the elapsed time as seconds.
             * This function returns the time elapsed since the last call to restart() (or the construction of the instance if restart() has not been called).
             * @return float Time elapsed as seconds
             */
            float GetElapsedTimeAsSeconds()
            {
                return (_clock.getElapsedTime().asSeconds());
            }

            /**
             * @brief Get the elapsed time as milliseconds.
             * 
             * @return signed int Time elapsed as milliseconds
             */
            signed int GetElapsedTimeAsMilliseconds()
            {
                return (_clock.getElapsedTime().asMilliseconds());
            }

            /**
             * @brief Get the elapsed time as microseconds.
             *
             * @return signed long long Time elapsed as microseconds.
             */
            signed long long GetElapsedTimeAsMicroseconds()
            {
                return (_clock.getElapsedTime().asMicroseconds());
            }

            /**
             * @brief Restart the clock.
             * This function puts the time counter back to zero. It also returns the time elapsed since the clock was started.
             * @return float Time elapsed
             */
            float Restart()
            {
                return (_clock.restart().asSeconds());
            }

            /**
             * @brief Return the current clock
             * 
             * @return sf::Clock& Current clock
             */
            sf::Clock &GetClock()
            {
                return (_clock);
            }
    };
}