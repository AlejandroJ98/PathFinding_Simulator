#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 SeekBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 posToGoal = agent.destination - agent.position;
	X::Math::Vector2 direction = X::Math::Normalize(posToGoal);
	X::Math::Vector2 desiredVelocity = direction * agent.maxSpeed;
	X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
	return seekForce;
}

X::Math::Vector2 SeekBehavior2::Calculate(Agent& agent)
{
	return { 200.0f, 0.0f };
}

X::Math::Vector2 FleeBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 posToGoal = agent.position - agent.destination;
	X::Math::Vector2 direction = X::Math::Normalize(posToGoal);
	X::Math::Vector2 desiredVelocity = direction * agent.maxSpeed;
	X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
	return seekForce;
}

X::Math::Vector2 ArriveBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 posToGoal = agent.destination - agent.position;
	double dist = X::Math::Magnitude(posToGoal);//length
	if (dist > 0)
	{
		const double Decel = 1.0f;
		double speed = dist / (2 * Decel);
		speed = X::Math::Min(speed, (double)agent.maxSpeed);
		X::Math::Vector2 direction = X::Math::Normalize(posToGoal);
		X::Math::Vector2 desiredVelocity = posToGoal * speed / dist;
		X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
		return seekForce;
	}
	return{ 0.0f, 0.0f };
}