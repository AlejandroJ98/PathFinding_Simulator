#pragma once

#include "Common.h"

namespace AI
{
	class Agent; //Better way instead of using #include
	class SteeringBehavior
	{

	public:
		SteeringBehavior() = default;
		virtual ~SteeringBehavior() = default;

		virtual X::Math::Vector2 Calculate(Agent& agent) = 0;

		void SetActive(bool active) { mActive = active; }
		bool IsActive() const { return mActive; }

	private:
		bool mActive = false;
	};
}