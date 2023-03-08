#pragma once

#include "Common.h"

namespace AI
{
	class Entity;
	class AIWorld;

	using Entities = std::vector<Entity*>;

	class Entity
	{
	public:
		Entity(AIWorld& world, uint32_t typeId);
		virtual ~Entity();

		Entity(const Entity&) = delete;

		AIWorld& world;
		X::Math::Vector2 position;
		X::Math::Vector2 heading;
		const uint64_t id;
		float radius = 1.0f;
	};
}