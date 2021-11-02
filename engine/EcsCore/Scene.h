/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Scene
*/

#pragma once

#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Types.h"
#include <memory>

class Scene
{
private:
	std::unique_ptr<ComponentManager> _ComponentManager;
	std::unique_ptr<EntityManager> _EntityManager;
	std::unique_ptr<SystemManager> _SystemManager;

public:
	void Init()
	{
		_ComponentManager = std::make_unique<ComponentManager>();
		_EntityManager = std::make_unique<EntityManager>();
		_SystemManager = std::make_unique<SystemManager>();
	}

	// Entity methods
	Entity CreateEntity()
	{
		return _EntityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		_EntityManager->DestroyEntity(entity);

		_ComponentManager->EntityDestroyed(entity);

		_SystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		_ComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		_ComponentManager->AddComponent<T>(entity, component);

		auto signature = _EntityManager->GetSignature(entity);
		signature.set(_ComponentManager->GetComponentType<T>(), true);
		_EntityManager->SetSignature(entity, signature);

		_SystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		_ComponentManager->RemoveComponent<T>(entity);

		auto signature = _EntityManager->GetSignature(entity);
		signature.set(_ComponentManager->GetComponentType<T>(), false);
		_EntityManager->SetSignature(entity, signature);

		_SystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return _ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return _ComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return _SystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(EntitySignature signature)
	{
		_SystemManager->SetSignature<T>(signature);
	}
};