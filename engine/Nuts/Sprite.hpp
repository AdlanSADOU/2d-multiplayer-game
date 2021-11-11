/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Sprite
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Texture.hpp"
#include "Rect.hpp"

class Sprite
{
    private:
        sf::Sprite _sprite;

        bool _is_animated = false;

    public:
        Sprite::Sprite()
        {

        }

        Sprite::~Sprite()
        {

        }

        void SetTexture(const Texture &texture)
        {
            _sprite.setTexture(texture.GetTexture());
        }

        void SetTextureRect(const IntRect &rect)
        {
            _sprite.setTextureRect({rect.left,
                                    rect.top,
                                    rect.width,
                                    rect.height});
        }

        void SetAnimated(bool animate)
        {
            _is_animated = animate;
        }

        bool IsAnimated() const
        {
            return (_is_animated);
        }
};
