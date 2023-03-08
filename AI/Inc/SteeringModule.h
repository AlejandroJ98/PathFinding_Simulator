#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class SteeringModule
	{
	public:
		SteeringModule(Agent& agent);

		template<class BehaviorType>
		BehaviorType* AddBehavior()
		{
			static_assert(std::is_base_of_v<SteeringBehavior, BehaviorType>, "Behaviortype is not a child class of AI::SteeringBehavior!");
			auto& newBehavior = mBehaviors.emplace_back(std::make_unique<BehaviorType>());
			return static_cast<BehaviorType*>(newBehavior.get());
		}

		X::Math::Vector2 Calculate();

	private:
		using Behaviors = std::vector<std::unique_ptr<SteeringBehavior>>;

		Agent& mAgent;
		Behaviors mBehaviors;
	};
}