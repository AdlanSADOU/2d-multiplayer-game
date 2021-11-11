/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Texture
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>

class Texture
{
    public:
        Texture::Texture()
        {

        }

        Texture::~Texture()
        {

        }

        void LoadFromFile(const std::string &path)
        {
            _texture.loadFromFile(path.c_str());
        }

        sf::Texture GetTexture() const
        {
            return (this->_texture);
        }

    protected:
    private:
        sf::Texture _texture;
};
