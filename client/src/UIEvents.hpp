/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** UIEvents.hpp
*/

#pragma once

#include <Nuts/EcsCore/Event.hpp>

namespace Events::Btn {
    const EventType BTN_LOBBY_SCREEN = HASH(Events::BTN_LOBBY_SCREEN);
    const EventType BTN_QUIT         = HASH(Events::BTN_QUIT);
    const EventType BTN_START         = HASH(Events::BTN_START);
} // namespace nuts::UI
