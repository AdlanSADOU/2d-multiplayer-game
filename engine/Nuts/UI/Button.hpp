/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Button.hpp
*/

#include "Widget.hpp"

extern Scene scene;

namespace nuts::UI {

    class Button : public Widget {
    private:
        EventType _type;

    public:
        Button() {};
        ~Button() {};

        Button(std::string name)
            : Widget(name)
        {
            Create(name);
        }

        void SetEventType(EventType type)
        {
            _type = type;
        }

        void InvokeEvent(Event &event)
        {
            scene.InvokeEvent(event);
        }

        void InvokeEvent(EventType eventType)
        {
            scene.InvokeEvent(eventType);
        }
    };
}