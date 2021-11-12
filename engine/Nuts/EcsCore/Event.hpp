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
#include <SFML/Config.hpp>

using EventType   = std::int32_t;
using ParameterId = std::int32_t;

#define BIND_CALLBACK(_callback, _classInstance) (std::bind(_callback, _classInstance, std::placeholders::_1))

class Event
{
private:
    EventType _eventType;

    std::unordered_map<ParameterId, std::any> _parameters {};

public:
    Event(EventType type)
    {
        _eventType = type;
        // event is added but not called for some reason
    }

    template <typename ParameterType>
    void SetParam(ParameterId id, ParameterType value)
    {
        _parameters[id] = value;
    }

    template <typename ParameterType>
    ParameterType GetParam(ParameterId id)
    {
        return std::any_cast<ParameterType>(_parameters[id]);
    }

    EventType GetType() const
    {
        return _eventType;
    }
};
