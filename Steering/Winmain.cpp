#include"SCV.h"
#include<AI.h>
#include <XEngine.h>

AI::AIWorld world;
std::vector<std::unique_ptr<SCV>> scvs;

void GameInit()
{
	for (int i = 0; i < 10; ++i)
	{
		auto& scv = scvs.emplace_back(std::make_unique<SCV>(world));
		scv->Initialize();
		scv->position.x = X::RandomFloat(100.0f, 900.0f);
		scv->position.y = X::RandomFloat(100.0f, 600.0f);
	}
}

bool GameLoop(float deltaTime)
{
	for (auto& scv : scvs)
	{
		if (X::IsMousePressed(X::Mouse::LBUTTON))
		{
			scv->destination.x = (float)X::GetMouseScreenX();
			scv->destination.y = (float)X::GetMouseScreenY();
		}


		if (X::IsKeyPressed(X::Keys::ONE))
		{
			scv->SetSeek(true);
			scv->SetSeek2(false);
			scv->SetFlee(false);
			scv->SetArrive(false);
		}
		if (X::IsKeyPressed(X::Keys::TWO))
		{
			scv->SetSeek(false);
			scv->SetSeek2(true);
			scv->SetFlee(false);
			scv->SetArrive(false);
		}
		if (X::IsKeyPressed(X::Keys::THREE))
		{
			scv->SetSeek(false);
			scv->SetSeek2(false);
			scv->SetFlee(true);
			scv->SetArrive(false);
		}
		if (X::IsKeyPressed(X::Keys::FOUR))
		{
			scv->SetSeek(false);
			scv->SetSeek2(false);
			scv->SetFlee(false);
			scv->SetArrive(true);
		}
		scv->Update(deltaTime);
	}
	

	for (auto& scv : scvs)
		scv->Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}