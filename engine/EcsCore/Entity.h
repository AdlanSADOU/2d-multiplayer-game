/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Entity.h
*/

#pragma once

#include "Types.h"
#include <any>
#include <unordered_map>

class Event
{
public:
	explicit Event(EventId type)
		: mType(type)
	{}

	template<typename T>
	void SetParam(EventId id, T value)
	{
		mData[id] = value;
	}

	template<typename T>
	T GetParam(EventId id)
	{
		return std::any_cast<T>(mData[id]);
	}

	EventId GetType() const
	{
		return mType;
	}

private:
	EventId mType{};
	std::unordered_map<EventId, std::any> mData{};
};