/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Text
*/

#pragma once

#include <SFML/Graphics/Text.hpp>

#include "../Color.hpp"

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

            void SetFillColor(nuts::Color &color)
            {
                _text.setFillColor({color.r, color.g, color.b, color.a});
            }

            void SetCharacterSize(unsigned int size)
            {
                _text.setCharacterSize(size);
            }

            void SetOutlineThickness(float thickness)
            {
                _text.setOutlineThickness(thickness);
            }

            void SetLetterSpacing(float spacingFactor)
            {
                _text.setLetterSpacing(spacingFactor);
            }

            void SetLineSpacing(float spacingFactor)
            {
                _text.setLineSpacing(spacingFactor);
            }

            const std::string &GetString()
            {
                return (_text.getString());
            }

            const sf::Font *GetFont()
            {
                return (_text.getFont());
            }
    };
}
