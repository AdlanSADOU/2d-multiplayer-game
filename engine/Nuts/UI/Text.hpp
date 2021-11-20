/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Text
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "../Color.hpp"
#include "../Rect.hpp"
#include "Vect.hpp"

#include <iostream>

namespace nuts
{
    class Font
    {
        private:
            sf::Font _font;
        public:
            Font()
            {

            }

            ~Font()
            {

            }

            bool LoadFromFile(const std::string &path)
            {
                return (_font.loadFromFile(path));
            }

            const sf::Font &GetFont()
            {
                return (_font);
            }
    };

    class Text
    {
        private:
            sf::Text _text;

        public:
            Text()
            {

            }

            Text(const std::string &text, const unsigned int size, nuts::Font &font)
            {
                this->SetFont(font);
                this->SetString(text);
                this->SetCharacterSize(size);
            }

            ~Text()
            {

            }

            void SetFont(nuts::Font &font)
            {
                _text.setFont(font.GetFont());
            }

            void SetString(const std::string &string)
            {
                _text.setString(string);
            }

            void SetOulineColor(nuts::Color &color)
            {
                _text.setOutlineColor({color.r, color.g, color.b, color.a});
            }

            void SetFillColor(nuts::Color color)
            {
                _text.setFillColor({color.r, color.g, color.b, color.a});
            }

            void SetCharacterSize(const unsigned int size)
            {
                _text.setCharacterSize(size);
            }

            void SetOutlineThickness(const float thickness)
            {
                _text.setOutlineThickness(thickness);
            }

            void SetLetterSpacing(const float spacingFactor)
            {
                _text.setLetterSpacing(spacingFactor);
            }

            void SetLineSpacing(const float spacingFactor)
            {
                _text.setLineSpacing(spacingFactor);
            }

            void SetPosition(const nuts::Vector2f &pos)
            {
                _text.setPosition({pos.x, pos.y});
            }

            void SetRotation(const float angle)
            {
                _text.setRotation(angle);
            }

            void SetOrigin(const nuts::Vector2f &origin)
            {
                _text.setOrigin({origin.x, origin.y});
            }

            nuts::FloatRect GetLocalBounds()
            {
                sf::FloatRect rect = _text.getLocalBounds();
                return {rect.left, rect.top, rect.width, rect.height};
            }

            nuts::FloatRect GetGlobalBounds()
            {
                sf::FloatRect rect = _text.getGlobalBounds();
                return {rect.left, rect.top, rect.width, rect.height};
            }

            const std::string GetString()
            {
                return (_text.getString());
            }

            const sf::Font *GetFont()
            {
                return (_text.getFont());
            }

            void TEST_DRAW(sf::RenderWindow &window)
            {
                window.draw(_text);
            }
    };
}
