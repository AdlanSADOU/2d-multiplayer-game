/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Nuts
*/

#pragma once

#include "EcsComponents/TransformComponent.hpp"

#include "Input.hpp"

#include <SFML/Graphics.hpp>

namespace nuts
{
    class Engine
    {
        private:
            nuts::Key pressedKey;
            nuts::Key downKey;
            bool isRunning;

        public:
            sf::RenderWindow window;

            void InitWindow(char const *windowName, std::uint32_t width, std::uint32_t height)
            {
                window.create({width, height, 32}, windowName);
                isRunning = true;
            }

            void SetFramerateLimit(unsigned int limit)
            {
                window.setFramerateLimit(limit);
            }

            void Clear(uint8_t r = 0U, uint8_t g = 0U, uint8_t b = 0U, uint8_t a = 255U)
            {
                window.clear({r, g, b, a});
            }

            void Present()
            {
                window.display();
            }

            bool IsRunning()
            {
                return window.isOpen();
            }

            void CloseWindow()
            {
                window.close();
            }

            void HandleEvent()
            {
                sf::Event event;
                pressedKey = nuts::Unknown;

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    if (event.type == sf::Event::KeyPressed) {
                        pressedKey = (nuts::Key)event.key.code;
                        downKey = (nuts::Key)event.key.code;
                    }
                    if (event.type == sf::Event::KeyReleased) {
                        downKey = nuts::Unknown;
                    }
                }
            }

            bool GetKeyPressed(nuts::Key key)
            {
                if (key == pressedKey)
                    return true;
                return false;
            }

            bool GetKeyDown(nuts::Key key)
            {
                if (key == downKey)
                    return true;
                return false;
            }
    };

} // namespace nuts