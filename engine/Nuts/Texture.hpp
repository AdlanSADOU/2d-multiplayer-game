/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Texture
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>


namespace nuts
{
    class Texture
    {
        public:

            Texture()
            {

            }

            ~Texture()
            {

            }

            bool LoadFromFile(const std::string &path)
            {
                return (_texture.loadFromFile(path.c_str()));
            }

            sf::Texture &GetTexture()
            {
                return (this->_texture);
            }

        protected:
        private:
            sf::Texture _texture;
    };
} // namespace nuts
