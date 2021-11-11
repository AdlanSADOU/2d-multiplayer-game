/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Rect
*/

#pragma once

namespace nuts
{
    typedef struct
    {
        int left;
        int top;
        int width;
        int height;
    } IntRect;

    typedef struct
    {
        float left;
        float top;
        float width;
        float height;
    } FloatRect;
}