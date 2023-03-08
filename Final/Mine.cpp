#include "Mine.h"

Mine& Mine::Get()
{
	static Mine instance;
	return instance;
}
void Mine::Initialize()
{
	mPosition = { 500.0f, 320.0f };
	mTextureId = X::LoadTexture("minerals.png");
}

void Mine::Render()
{
	X::DrawSprite(mTextureId, mPosition);
}

