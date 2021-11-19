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

#include <iostream>

namespace nuts {
    class Engine
    {
    private:
        nuts::Key            pressedKey  = nuts::Unknown;
        nuts::Key            releasedKey  = nuts::Unknown;
        nuts::Key            downKey     = nuts::Unknown;
        nuts::Button         mouseButton = nuts::Button::Middle;
        nuts::Vector2i       mousePos;
        bool                 isRunning;
        sf::Event::EventType type;
        bool                 isPressed = false;

    public:
        sf::RenderWindow window;

        void InitWindow(char const *windowName, std::uint32_t width, std::uint32_t height)
        {
            window.create({ width, height, 32 }, windowName);
            isRunning = true;
        }

        void SetFramerateLimit(unsigned int limit)
        {
            window.setFramerateLimit(limit);
        }

        void Clear(uint8_t r = 0U, uint8_t g = 0U, uint8_t b = 0U, uint8_t a = 255U)
        {
            window.clear({ r, g, b, a });
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
            // pressedKey  = nuts::Unknown;
            mouseButton = nuts::Button::Middle;

            while (window.pollEvent(event)) {

                type = event.type;

                if (event.type == sf::Event::Closed)
                    window.close();

                if (type == sf::Event::KeyPressed) {
                    pressedKey = (nuts::Key)event.key.code;
                    downKey    = (nuts::Key)event.key.code;
                }
                if (type == sf::Event::KeyReleased) {
                    releasedKey = (nuts::Key)event.key.code;
                }
                if (event.type == sf::Event::KeyReleased && event.key.code == (sf::Keyboard::Key)pressedKey) {
                    downKey    = nuts::Unknown;
                    pressedKey = nuts::Unknown;
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    mouseButton = (nuts::Button)event.mouseButton.button;
                }
                if (event.type == sf::Event::MouseMoved) {
                    mousePos = { event.mouseMove.x, event.mouseMove.y };
                }
            }


        }

        bool IskeyEvent()
        {
            if (type == sf::Event::KeyPressed)
                return true;
            return false;
        }

        nuts::Key GetPressedKey()
        {
            return pressedKey;
        }

        nuts::Key GetDownKey()
        {
            return downKey;
        }

        bool IsKeyPressed(nuts::Key key)
        {
            if (key == pressedKey)
                return true;
            return false;
        }
        bool IsKeyReleased(nuts::Key key)
        {
            if (key == releasedKey)
                return true;
            return false;
        }

        bool IsKeyDown(nuts::Key key)
        {
            if (key == downKey)
                return true;
            return false;
        }

        bool IsMouseBtnPressed(nuts::Button mouseBtn)
        {
            return (mouseButton == mouseBtn);
        }

        nuts::Vector2i GetMousePos() const
        {
            return mousePos;
        }

        nuts::Vector2u GetWindowSize() const
        {
            return { window.getSize().x, window.getSize().y };
        }
    };

} // namespace nuts
