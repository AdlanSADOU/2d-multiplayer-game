/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** GameObject
*/

#pragma once

#include <EcsCore/Scene.hpp>
#include <string>

extern Scene gScene;

/** TODO(adlan):
 * GameObjects should handle their own Components
 * it should implement its own array of components
 */
class GameObject {
private:
    std::string _name;
    Entity _entity;

public:
    GameObject() {};

    GameObject(std::string name)
    {
        Create(name);
    };

    void Create(std::string name)
    {
        _name = name;
        _entity = gScene.CreateEntity();
    }

    template <typename T>
    void AddComponent()
    {
        gScene.AddComponent(_entity, T {});
    };

    template <typename T>
    void RemoveComponent()
    {

        }

    template <typename T>
    T &GetComponent()
    {
        return gScene.GetComponent<T>(_entity);
    }

        Entity GetEntity()
        {
            return _entity;
        }
};
