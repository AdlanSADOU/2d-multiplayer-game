/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** GameObject
*/

#pragma once

#include "EcsCore/Scene.hpp"

#include <string>

extern Scene scene;

namespace nuts {
class GameObject {
protected:
    std::string _name;
    Entity _entity;

public:
    GameObject()
    {
    }

    GameObject(std::string name)
    {
        Create(name);
    }

    void Create(std::string name)
    {
        _name = name;
        _entity = scene.CreateEntity();
    }

    template <typename T>
    void AddComponent()
    {
        scene.AddComponent(_entity, T {});
    }

    template <typename T>
    void RemoveComponent()
    {
        scene.RemoveComponent<T>(_entity);
    }

    template <typename T>
    T& GetComponent()
    {
        return scene.GetComponent<T>(_entity);
    }

    Entity GetEntity() const
    {
        return _entity;
    }

    std::string GetName() const
    {
        return _name;
    }
};

} // namespace nuts
