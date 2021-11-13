/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Event.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <list>
#include <unordered_map>
#include <string>

using EventType   = std::size_t;
using ParameterId = std::int32_t;


#if !defined(HASH)

/**
 * @brief The string hasher is used in the context of the Event system to
 * avoid having to keep track of enum values for different event types.
 * The hasher solves this by attributing a "unique" size_t value based on
 * the namespace + event name of the EventType.
 * The downside is that, for network events, size_t is quite large.
 *
 * @see Nuts/Networking.hpp
 */
static const std::hash<std::string> strHasher;
#define HASH(x) (strHasher(#x))
#endif

/**
 * @brief Bind class member function pointer to its class instance
 */
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
