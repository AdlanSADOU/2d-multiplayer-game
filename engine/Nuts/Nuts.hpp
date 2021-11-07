/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Nuts
*/

#pragma once

#include "EcsComponents/TransformComponent.hpp"
#include <SFML/Graphics.hpp>
#include <Input.hpp>

class Nuts {
public:
    sf::RenderWindow window;

    private:
        sf::Keyboard::Key pressedKey;
        sf::Keyboard::Key downKey;
        bool isRunning;

public:
    void InitWindow(char* windowName, std::uint32_t width, std::uint32_t height)
    {
        window.create({ width, height, 32 }, windowName);
        isRunning = true;
    };

    void Clear()
    {
        window.clear();
    };

        void Clear()
        {
            window.clear();
        };

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

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                pressedKey = event.key.code;
                downKey = event.key.code;
            }
            if (event.type == sf::Event::KeyReleased) {
                downKey = sf::Keyboard::Unknown;
            }
        };

    bool GetKeyPressed(Input::Key key)
    {
        if (key == pressedKey)
            return true;
        return false;
    }

        bool GetKeyDown(sf::Keyboard::Key key)
        {
            if (key == downKey)
                return true;
            return false;
        }
};
