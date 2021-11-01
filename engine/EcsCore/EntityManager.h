/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** EntityManager.h
*/

#pragma once

#include "Types.h"
#include <array>
#include <cassert>
#include <queue>


class EntityManager
{
public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mEntitiesPool.push(entity);
		}
	}

	Entity CreateEntity()
	{
		assert(mExistingEntitiesCount < MAX_ENTITIES && "Too many entities in existence.");

		Entity id = mEntitiesPool.front();
		mEntitiesPool.pop();
		++mExistingEntitiesCount;

		return id;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity].reset();
		mEntitiesPool.push(entity);
		--mExistingEntitiesCount;
	}

	void SetSignature(Entity entity, EntitySignature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity] = signature;
	}

	EntitySignature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		return mSignatures[entity];
	}

private:
	std::queue<Entity> mEntitiesPool{};
	std::array<EntitySignature, MAX_ENTITIES> mSignatures{};
	uint32_t mExistingEntitiesCount{};
};