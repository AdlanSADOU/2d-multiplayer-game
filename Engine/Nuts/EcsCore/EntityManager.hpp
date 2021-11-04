/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** EntityManager.h
*/

#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <queue>

class EntityManager
{
    private:
        std::queue<Entity> _EntitiesPool{};
        std::array<EntitySignature, MAX_ENTITIES> _Signatures{};
        uint32_t _ExistingEntitiesCount{};

    public:
        EntityManager()
        {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
            {
                _EntitiesPool.push(entity);
            }
        }

        Entity CreateEntity()
        {
            assert(_ExistingEntitiesCount < MAX_ENTITIES && "Too many entities in existence.");

            Entity id = _EntitiesPool.front();
            _EntitiesPool.pop();
            ++_ExistingEntitiesCount;

            return id;
        }

        void DestroyEntity(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            _Signatures[entity].reset();
            _EntitiesPool.push(entity);
            --_ExistingEntitiesCount;
        }

        void SetSignature(Entity entity, EntitySignature signature)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            _Signatures[entity] = signature;
        }

        EntitySignature GetSignature(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            return _Signatures[entity];
        }
};