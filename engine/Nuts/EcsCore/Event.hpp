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
#define HASH(x) (hasher("x"))

namespace Events::Window {
const EventType QUIT = HASH(Window::QUIT);
const EventType RESIZED = HASH(Window::RESIZED);
}

namespace Events::Net {
const EventType CLIENT_CONNECT = HASH(Net::CLIENT_CONNECT);
const EventType CLIENT_DISCONNECT = HASH(Net::CLIENT_DISCONNECT);
const EventType CLIENT_ID = HASH(Net::CLIENT_ID);
const EventType CLIENTS_PRINT = HASH(Net::CLIENTS_PRINT);
const EventType UDP_INFO = HASH(Net::UDP_INFO);
const EventType UDP_OK = HASH(Net::UDP_OK);
const EventType LOBBY_LOAD = HASH(Net::LOBBY_LOAD);
const EventType LOBBY_LIST = HASH(Net::LOBBY_LIST);
const EventType LOBBY_CREATE = HASH(Net::LOBBY_CREATE);
const EventType LOBBY_JOIN = HASH(Net::LOBBY_JOIN);
const EventType LOBBY_CLIENTS = HASH(Net::LOBBY_CLIENTS);
const EventType LOBBY_QUIT = HASH(Net::LOBBY_QUIT);
const EventType LOBBY_READY = HASH(Net::LOBBY_READY);
const EventType LOBBY_READY_OK = HASH(Net::LOBBY_READY_OK);
const EventType LOBBY_CANCEL = HASH(Net::LOBBY_CANCEL);
const EventType LOBBY_CANCEL_OK = HASH(Net::LOBBY_CANCEL_OK);
}

class Event {
private:
    EventType _eventType;
    std::unordered_map<ParameterId, std::any> _paramaters {};

public:
    Event(EventType type)
    {
        _eventType = type;
        // event is added but not called for some reason
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
