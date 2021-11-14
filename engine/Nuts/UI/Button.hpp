/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Button.hpp
*/

#pragma once

#include "Widget.hpp"
#include "Text.hpp"

extern Scene scene;

namespace nuts::UI
{
    class Button : public Widget
    {
        private:
            EventType _type;
            nuts::Text _text;

        public:
            Button() {};
            ~Button() {};

            Button(std::string name) : Widget(name)
            {
                Create(name);
            }

            void SetText(const std::string &text)
            {
                _text.SetString(text);
            }

            void SetFont(nuts::Font &font)
            {
                _text.SetFont(font);
            }

            void SetEventType(EventType type)
            {
                _type = type;
            }

            void InvokeEvent(Event event)
            {
                std::cout << "invoked eventType: " << event.GetType() << "\n";
                scene.InvokeEvent(event);
            }

            void InvokeEvent(EventType eventType)
            {
                scene.InvokeEvent(eventType);
            }

            bool IsHovered(const nuts::Vector2i mousePos)
            {
                auto sprite = Widget::GetSprite().GetSprite();
                auto btnPos = Widget::GetSprite().GetPosition();

                return sprite.getGlobalBounds().contains({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
            }
    };
}