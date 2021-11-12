/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** WidgetComponent.hpp
*/

#pragma once

#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

struct WidgetComponent
{
    nuts::Sprite       sprite;
    bool               isActive;
};