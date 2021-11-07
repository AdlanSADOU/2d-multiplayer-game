/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Nuts
*/

#pragma once

#include "EcsComponents/TransformComponent.hpp"
#include <SFML/Graphics.hpp>
#include "Input.hpp"

class Nuts {
    private:
        Input::Key pressedKey;
        Input::Key downKey;
        bool isRunning;

    public:
        sf::RenderWindow window;

        void InitWindow(char const *windowName, std::uint32_t width, std::uint32_t height)
        {
            window.create((sf::VideoMode){width, height, 32}, windowName);
            isRunning = true;
        }

        void SetFramerateLimit(unsigned int limit)
        {
            window.setFramerateLimit(limit);
        }

        void Clear()
        {
            window.clear();
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
            pressedKey = Input::Unknown;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed) {
                    pressedKey = (Input::Key)event.key.code;
                    downKey = (Input::Key)event.key.code;
                }
                if (event.type == sf::Event::KeyReleased) {
                    downKey = Input::Unknown;
                }
            }
        }

        bool GetKeyPressed(Input::Key key)
        {
            if (key == pressedKey)
                return true;
            return false;
        }

        bool GetKeyDown(Input::Key key)
        {
            if (key == downKey)
                return true;
            return false;
        }
};
