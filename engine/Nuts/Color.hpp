/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Color
*/

#pragma once

#include <SFML/Graphics/Text.hpp>

namespace nuts
{
    /**
     * @brief Color defined by RGBA color code.
     * 
     */
    typedef struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } Color;
}
