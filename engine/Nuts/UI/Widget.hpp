/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** widget.hpp
*/

#pragma once

#include "EcsComponents/SpriteComponent.hpp"
#include "EcsComponents/TransformComponent.hpp"
#include "GameObject.hpp"

extern Scene scene;

namespace nuts {

    struct WidgetComponent
    {
        SpriteComponent    sprite;
        TransformComponent transform;
        WidgetComponent *  parent;
        bool               isActive;
    };

    class Widget
    {
    private:
        nuts::GameObject        _gameObject;
        std::string             _name;
        std::shared_ptr<Widget> _parent;

    public:

        void Create(std::string name)
        {
            _name = name;
            _gameObject.Create(name);
            _gameObject.AddComponent<WidgetComponent>();
        }

        void SetParent(Widget &parent)
        {
            _parent = std::make_shared<Widget>(parent);
        }

        std::shared_ptr<Widget> GetParent() const
        {
            return _parent;
        }
    };
}