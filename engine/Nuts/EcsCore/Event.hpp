/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Event.hpp
*/

#pragma once

#include <any>
#include <cstdint>
#include <functional>
#include <list>
#include <unordered_map>

using EventType = std::size_t;
using ParameterId = std::int32_t;
#define BIND_CALLBACK(_callback, _classInstance) (std::bind(_callback, _classInstance, std::placeholders::_1))

std::hash<char*> hasher;
#define HASH(x)(hasher("x"))

namespace Events::Window {
const EventType QUIT = HASH(Window::QUIT);
const EventType RESIZED = HASH(Window::RESIZED);
}

namespace Events::Net {
const EventType CLIENT_CONN = HASH(Net::CLIENT_CONN);
const EventType UDP_INFO = HASH(Net::UDP_INFO);
const EventType DISCONNECT = HASH(Net::DISCONNECT);
}

class Event {
private:
    EventType _eventType;
    std::unordered_map<ParameterId, std::any> _paramaters {};

public:
    Event(EventType type)
    {
        _eventType = type;
    }

    template <typename ParamaterType>
    void SetParam(ParameterId id, ParamaterType value)
    {
        _paramaters[id] = value;
    }

    template <typename ParamaterType>
    ParamaterType GetParam(ParameterId id)
    {
        return std::any_cast<ParamaterType>(_paramaters[id]);
    }

    EventType GetType() const
    {
        return _eventType;
    }
};
