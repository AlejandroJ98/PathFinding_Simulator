#include "SCV.h"

SCV::SCV(AI::AIWorld& world)
	:AI::Agent(world, 0)
{

}

void SCV::Initialize()
{
	//set agent attribute
	maxSpeed = 200.0f;

	//Locomotion
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	mSeekBehavior2 = mSteeringModule->AddBehavior<AI::SeekBehavior2>();
	mFleeBehavior = mSteeringModule->AddBehavior<AI::FleeBehavior>();
	mFleeBehavior->panicDistance = 500.0f;
	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();

	for (size_t i = 0; i < mTextureIds.size(); ++i)
	{
		char name[256];
		sprintf_s(name, "scv_%02zu.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}

}

void SCV::Update(float deltaTime)
{
	auto force = mSteeringModule->Calculate();

	auto acceleration = force / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;

	//if we have any movement at all, update the heading direction
	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
		heading = X::Math::Normalize(velocity);
}

void SCV::Render()
{
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	float percent = angle / X::Math::kTwoPi;
	int frame = (int)(percent * mTextureIds.size()) % mTextureIds.size();
	X::DrawSprite(mTextureIds[frame], position);

	X::DrawScreenCircle(destination, 30.0f, X::Colors::Red); 
}

