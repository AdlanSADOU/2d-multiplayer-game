/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SpriteComponent
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct SpriteComponent {
    sf::Texture texture;
    sf::Sprite sprite;
    bool isActive = false;
};
