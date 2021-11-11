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
    class Clock
    {
        private:
            sf::Clock _clock;

        public:
            Clock()
            {

            }

            ~Clock()
            {

            }

            float GetElapsedTimeAsSeconds()
            {
                return (_clock.getElapsedTime().asSeconds());
            }

            signed int GetElapsedTimeAsMilliseconds()
            {
                return (_clock.getElapsedTime().asMilliseconds());
            }

            signed long long GetElapsedTimeAsMicroseconds()
            {
                return (_clock.getElapsedTime().asMicroseconds());
            }

            void Restart()
            {
                _clock.restart();
            }
    };
}