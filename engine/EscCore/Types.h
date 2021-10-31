#pragma once

#include <bitset>
#include <cstdint>

// ECS
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using EntitySignature = std::bitset<MAX_COMPONENTS>;

// Input
enum class InputButtons
{
	W,
	A,
	S,
	D,
	Q,
	E
};

// Events
using EventId = std::uint32_t;
using ParamId = std::uint32_t;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)
