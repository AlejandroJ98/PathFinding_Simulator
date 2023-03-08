#pragma once

#include <AI.h>
#include <XEngine.h>

class SCV :public AI::Agent
{
public:
	SCV(AI::AIWorld& world);
	void Initialize();

	void Update(float deltaTime);
	void Render();

	void SetSeek(bool active) { mSeekBehavior->SetActive(active); }
	void SetSeek2(bool active) { mSeekBehavior2->SetActive(active); }
	void SetFlee(bool active) { mFleeBehavior->SetActive(active); }
	void SetArrive(bool active) { mArriveBehavior->SetActive(active); }

private:
	std::unique_ptr<AI::SteeringModule>mSteeringModule;
	std::array<X::TextureId, 16>mTextureIds;

	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::SeekBehavior2* mSeekBehavior2 = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
};