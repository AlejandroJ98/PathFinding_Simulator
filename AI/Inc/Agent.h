#pragma once

#include "Entity.h"

namespace AI
{
	class Agent;

	using Agents = std::vector<Agent*>;

	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeId);
		~Agent() override = default;

		X::Math::Vector2 velocity;
		X::Math::Vector2 destination;
		float maxSpeed = 1.0f;
		float mass = 1.0f;
	};
}