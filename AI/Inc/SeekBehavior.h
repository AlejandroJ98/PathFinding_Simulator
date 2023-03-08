#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class SeekBehavior : public AI::SteeringBehavior
	{

	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
	
	class SeekBehavior2 : public AI::SteeringBehavior
	{

	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
	
	class FleeBehavior : public AI::SteeringBehavior
	{

	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		float panicDistance = 100.0f;
	};
	
	class ArriveBehavior : public AI::SteeringBehavior
	{
		
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}