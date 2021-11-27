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
#include <functional>

namespace nuts {
    class __declspec(dllexport) Engine
    {
    private:
        nuts::Key            _downKey     = nuts::Unknown;
        nuts::Key            _pressedKey  = nuts::Unknown;
        nuts::Key            _releasedKey = nuts::Unknown;
        nuts::Button         _mouseButton = nuts::Button::Middle;
        nuts::Vector2i       _mousePos;
        bool                 isRunning;
        sf::Event::EventType type;
        bool                 isPressed = false;

        sf::Clock deltaClock;

    public:
        sf::RenderWindow window;

        float dt;
        void  Clear();
        void  Present();
        void  HandleEvent();

        void InitWindow(char const *windowName, uint32_t width, uint32_t height);
        void SetFramerateLimit(unsigned int limit);
        bool IsRunning();
        void CloseWindow();
        bool IskeyEvent();
        bool IsKeyPressed(nuts::Key key);
        bool IsKeyReleased(nuts::Key key);
        bool IsKeyDown(nuts::Key key);
        bool IsMouseBtnPressed(nuts::Button mouseBtn);

        nuts::Key      GetPressedKey() const;
        nuts::Key      GetDownKey() const;
        nuts::Vector2i GetMousePos() const;
        nuts::Vector2u GetWindowSize() const;
    };

} // namespace nuts
