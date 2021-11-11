/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** EventManager.h
*/

#pragma once

#include "Event.hpp"

using Callback = std::function<void(Event&)>;

class EventManager
{
    private:
        std::unordered_map<EventType, std::list<Callback>> eventCallbacks;

    public:
        void AddEventCallback(EventType eventType, Callback const& callback)
        {
            eventCallbacks[eventType].push_back(callback);
        }

        void InvokeEvent(Event& event)
        {
            EventType eventType = event.GetType();

            for (auto const& callback : eventCallbacks[eventType]) {
                callback(event);
            }
        }

        void InvokeEvent(EventType eventType)
        {
            // for (auto const& callback : eventCallbacks[eventType]) {
            //     callback(Event(eventType));
            // }
        }
};
