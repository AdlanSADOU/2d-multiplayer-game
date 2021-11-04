/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** ComponentArray.h
*/

#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <unordered_map>

/** ////////////////////////////////////////////
 * @brief ComponentArray Interface needed to handle components
 * in a generic way.
 *
 */ //////////////////////////////////////////////
class IComponentArray
{
    public:
        virtual void EntityDestroyed(Entity entity) = 0;
};

/** ////////////////////////////////////////////
 * @brief Each entity has its templated array of components that are managed
 * by the ComponentManager.
 *
 *  @param T User defined type of component
 *
 *  @see ComponentManager
 *
 */
//////////////////////////////////////////////
template <typename T>
class ComponentArray : public IComponentArray
{
    private:
        std::array<T, MAX_ENTITIES> _ComponentArray{};
        std::unordered_map<Entity, size_t> _EntityToArrayIndexMap{};
        std::unordered_map<size_t, Entity> _ArrayIndexToEntityMap{};
        size_t mSize{};

    public:
        /** ////////////////////////////////////////////
         * @brief Adds given component to the ComponentArray attached to the given entity.
         *	This function is intended to be called by the ComponentManager and should not be called directly
        *
        *  @param Entity
        *
        *  @param T component
        *
        *  @see entity
        *
        */
        //////////////////////////////////////////////
        void InsertData(Entity entity, T component)
        {
            assert(_EntityToArrayIndexMap.find(entity) == _EntityToArrayIndexMap.end() && "Component added to same entity more than once.");

            // Put new entry at end
            size_t newIndex = mSize;
            _EntityToArrayIndexMap[entity] = newIndex;
            _ArrayIndexToEntityMap[newIndex] = entity;
            _ComponentArray[newIndex] = component;
            ++mSize;
        }

        /** ////////////////////////////////////////////
         * @brief Removes given component from the ComponentArray attached to the given entity.
         *	This function is intended to be called by the ComponentManager and should not be called directly
        *
        *  @param Entity
        *
        *  @see entity
        *
        */
        //////////////////////////////////////////////
        void RemoveData(Entity entity)
        {
            assert(_EntityToArrayIndexMap.find(entity) != _EntityToArrayIndexMap.end() && "Removing non-existent component.");

            // Copy last element into deleted element's place to maintain its contiguous nature
            size_t indexOfRemovedEntity = _EntityToArrayIndexMap[entity];
            size_t indexOfLastElement = mSize - 1;
            _ComponentArray[indexOfRemovedEntity] = _ComponentArray[indexOfLastElement];

            // Update map to point to moved spot
            Entity entityOfLastElement = _ArrayIndexToEntityMap[indexOfLastElement];
            _EntityToArrayIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            _ArrayIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            _EntityToArrayIndexMap.erase(entity);
            _ArrayIndexToEntityMap.erase(indexOfLastElement);

            --mSize;
        }

        T &GetData(Entity entity)
        {
            assert(_EntityToArrayIndexMap.find(entity) != _EntityToArrayIndexMap.end() && "Retrieving non-existent component.");

            return _ComponentArray[_EntityToArrayIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity) override
        {
            if (_EntityToArrayIndexMap.find(entity) != _EntityToArrayIndexMap.end())
            {
                RemoveData(entity);
            }
        }
};
