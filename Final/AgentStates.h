#pragma once

#include "Agent.h"
#include <AI.h>

class MoveState : public AI::State<Agent>
{
public:
	void Enter(Agent& agent) override;
	void Update(Agent& agent, float deltaTime) override;
	void Exit(Agent& agent) override;
private:
	float mWaitTime = 0.0f;
};


class SearchState : public AI::State<Agent>
{
public:
	void Enter(Agent& agent) override;
	void Update(Agent& agent, float deltaTime) override;
	void Exit(Agent& agent) override;
};

//class PickUpState : public AI::State<Agent>
//{
//public:
//	void Enter(Agent& agent) override;
//	void Update(Agent& agent, float deltaTime) override;
//	void Exit(Agent& agent) override;
//};

class MoveBack : public AI::State<Agent>
{
public:
	void Enter(Agent& agent) override;
	void Update(Agent& agent, float deltaTime) override;
	void Exit(Agent& agent) override;
};