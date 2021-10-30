/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Nuts
*/

#pragma once

#include <SFML/Graphics.hpp>

class Nuts
{
private:
    sf::RenderWindow window;
    sf::Keyboard::Key pressedKey;

public:

    void InitWindow(char *windowName, std::uint32_t width, std::uint32_t height)
    {
        window.create({width, height, 32}, windowName);
    };

    void Clear()
    {
        window.clear();
    };

    void Present()
    {
        window.display();
    }

    bool IsRunning(){
        return window.isOpen();
    }

    void HandleInput()
    {
        sf::Event event;
        pressedKey = sf::Keyboard::Unknown;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                pressedKey = event.key.code;
        }
    };

    bool GetKeyDown(sf::Keyboard::Key key)
    {
        if (key == pressedKey)
            return true;
        return false;
    }
};
