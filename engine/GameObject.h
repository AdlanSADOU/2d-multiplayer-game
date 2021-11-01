/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** GameObject
*/

#pragma once

#include <EcsCore/Scene.h>
#include <string>

class GameObject
{
private:
    std::shared_ptr<Scene> _scene;
    std::string _name;
    Entity _entity;

public:
    GameObject(){};

    GameObject(std::shared_ptr<Scene> scene, std::string name)
    {
        Create(scene, name);
    };

    void Create(std::shared_ptr<Scene> scene, std::string name)
    {
        _scene = scene;
        _name = name;
        _entity = _scene->CreateEntity();
    }

    template <typename T>
    void AddComponent()
    {
        _scene->AddComponent(_entity, T{});
    };

    void RemoveComponent()
    {

    }

    template <typename T>
    T GetComponent()
    {
       return _scene->GetComponent<T>(_entity);
    }

    Entity GetEntity()
    {
        return _entity;
    }
};
