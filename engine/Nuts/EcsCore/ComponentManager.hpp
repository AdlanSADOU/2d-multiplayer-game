/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** ComponentManager.h
*/

#pragma once

#include "ComponentArray.hpp"
#include "Types.hpp"
#include <any>
#include <memory>
#include <unordered_map>

class ComponentManager {

private:
    std::unordered_map<const char*, ComponentType> _ComponentTypes {};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _ComponentArrays {};
    ComponentType _NextComponentType {};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(_ComponentTypes.find(typeName) != _ComponentTypes.end() && "Component not connected before use.");

        return std::static_pointer_cast<ComponentArray<T>>(_ComponentArrays[typeName]);
    }

public:
    template <typename T>
    void RegisterComponent()
    {
        const char* typeName = typeid(T).name();

        assert(_ComponentTypes.find(typeName) == _ComponentTypes.end() && "Registering component type more than once.");

        _ComponentTypes.insert({ typeName, _NextComponentType });
        _ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

        ++_NextComponentType;
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        const char* typeName = typeid(T).name();

        assert(_ComponentTypes.find(typeName) != _ComponentTypes.end() && "Component not connected before use.");

        return _ComponentTypes[typeName];
    }

    template <typename T>
    void AddComponent(Entity entity, T component)
    {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template <typename T>
    void RemoveComponent(Entity entity) const
    {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template <typename T>
    T& GetComponent(Entity entity)
    {
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity)
    {
        for (auto const& pair : _ComponentArrays) {
            auto const& component = pair.second;

            component->EntityDestroyed(entity);
        }
    }
};