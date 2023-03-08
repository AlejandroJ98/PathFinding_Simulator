#pragma once

#include <AI.h>
#include <XEngine.h>

class Mine
{
public:
	static Mine& Get();
	void Initialize();

	void Render();

	//private:

	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;
};