#pragma once

#include <AI.h>
#include <XEngine.h>

class Agent
{
public:
	void Initialize();

	void Update(float deltaTime);
	void Render();

	const X::Math::Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }

	void ChangeState(const std::string& name);

	const X::TextureId& GetTexture() const { return mTextureId; }
	void SetTextureId(const X::TextureId& T) { mTextureId = T; }
	
	std::list<AI::GridBasedGraph::Node*> Path;


	private:
	std::unique_ptr<AI::StateMachine<Agent>> mStateMachine;

	X::TextureId mTextureId;

	X::Math::Vector2 mPosition;
}; 