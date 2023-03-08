#include "Agent.h"
#include "AgentStates.h"

void Agent::Initialize()
{
	mPosition = { 32.0f, 32.0f };
	// Create a state machine that controls this agent
	mStateMachine = std::make_unique<AI::StateMachine<Agent>>(*this);

	// Add states
	mStateMachine->AddState<MoveState>("MoveState"); // Default starting state
	mStateMachine->AddState<SearchState>("SearchState");
	/*mStateMachine->AddState<PickUpState>("PickUpState");*/
	mStateMachine->AddState<MoveBack>("MoveBackState");
	ChangeState("SearchState");
}

void Agent::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Agent::Render()
{
	X::DrawSprite(mTextureId, mPosition);
}

void Agent::ChangeState(const std::string& name)
{
	mStateMachine->ChangeState(name);
}
