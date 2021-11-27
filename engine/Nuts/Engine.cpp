/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Engine.cpp
*/

#include "Engine.hpp"

namespace nuts {
    void Engine::InitWindow(char const *windowName, uint32_t width, uint32_t height)
    {
        window.create({ width, height, 32 }, windowName);
        isRunning = true;
    }

    void Engine::SetFramerateLimit(unsigned int limit)
    {
        window.setFramerateLimit(limit);
    }

    void Engine::Clear()
    {
        window.clear();
    }

    void Engine::Present()
    {
        window.display();
    }

    bool Engine::IsRunning()
    {
        return window.isOpen();
    }

    void Engine::CloseWindow()
    {
        window.close();
    }

    void Engine::HandleEvent()
    {
        sf::Event event;
        // _pressedKey  = nuts::Unknown;
        _mouseButton = nuts::Button::Middle;
        // _pressedKey  = nuts::Unknown;
        // _releasedKey = nuts::Unknown;

        // _event = &event;
        while (window.pollEvent(event)) {

            type = event.type;

            if (event.type == sf::Event::Closed)
                window.close();

            if (type == sf::Event::KeyReleased) {
                _releasedKey = (nuts::Key)event.key.code;
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == (sf::Keyboard::Key)_pressedKey) {
                _downKey    = nuts::Unknown;
                _pressedKey = nuts::Unknown;
            }

            if (type == sf::Event::KeyPressed) {
                _pressedKey = (nuts::Key)event.key.code;
                _downKey    = (nuts::Key)event.key.code;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                _mouseButton = (nuts::Button)event.mouseButton.button;
            }

            if (event.type == sf::Event::MouseMoved) {
                _mousePos = { event.mouseMove.x, event.mouseMove.y };
            }
        }

        dt = deltaClock.restart().asSeconds();
    }

    bool Engine::IskeyEvent()
    {
        return (type == sf::Event::KeyPressed);
    }

    nuts::Key Engine::GetPressedKey() const
    {
        return _pressedKey;
    }

    nuts::Key Engine::GetDownKey() const
    {
        return _downKey;
    }

    bool Engine::IsKeyPressed(nuts::Key key)
    {
        return (key == _pressedKey);
    }

    bool Engine::IsKeyReleased(nuts::Key key)
    {
        return (key == _releasedKey);
    }

    bool Engine::IsKeyDown(nuts::Key key)
    {
        if (key == _downKey)
            return true;
        return false;
    }

    bool Engine::IsMouseBtnPressed(nuts::Button mouseBtn)
    {
        return (_mouseButton == mouseBtn);
    }

    nuts::Vector2i Engine::GetMousePos() const
    {
        return _mousePos;
    }

    nuts::Vector2u Engine::GetWindowSize() const
    {
        return { window.getSize().x, window.getSize().y };
    }
}