/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** SoundComponent
*/

#pragma once

#include "../Audio.hpp"

struct SoundComponent {
    nuts::Sound sound;
    bool shouldPlay = false;
};
