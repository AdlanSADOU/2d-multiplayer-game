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
    /**
     * @brief Image living on the graphics card that can be used for drawing.
     *
     */
    class Texture
    {
        public:

            /**
             * @brief Construct a new Texture object
             *
             */
            Texture()
            {

            }

            Texture(const std::string &path)
            {
                _texture.loadFromFile(path);
            }

            /**
             * @brief Destroy the Texture object
             *
             */
            ~Texture()
            {
                _texture.~Texture();
            }

            /**
             * @brief Load the texture from a file on disk.
             * This function is a shortcut for the following code:
             * sf::Image image;
             * image.loadFromFile(filename);
             * texture.loadFromImage(image, area);
             * The area argument can be used to load only a sub-rectangle of the whole image. If you want the entire image then leave the default value (which is an empty IntRect). If the area rectangle crosses the bounds of the image, it is adjusted to fit the image size.
             * The maximum size for a texture depends on the graphics driver and can be retrieved with the getMaximumSize function.
             * If this function fails, the texture is left unchanged.
             * @param path Path of the image file to load
             * @return True if loading was successful
             */
            bool LoadFromFile(const std::string &path)
            {
                return (_texture.loadFromFile(path));
            }

            /**
             * @brief Return the current texture.
             *
             * @return const sf::Texture&
             */
            const sf::Texture &GetTexture()
            {
                return (this->_texture);
            }

        protected:
        private:
            sf::Texture _texture;
    };
}
