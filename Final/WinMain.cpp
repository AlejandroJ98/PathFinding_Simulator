#include <AI.h>
#include <XEngine.h>
#include "TileMap.h"
#include <ImGui/Inc/imgui.h>
#include "Agent.h"
#include "Mine.h"

AI::AIWorld world;

Agent myAgent;

int startX = 0;
int startY = 0;
int endX = 0;
int endY = 0;

bool drawGraph = false;

std::list<AI::GridBasedGraph::Node*> nodePath;
std::list<AI::GridBasedGraph::Node*> closedList;




void GameInit()
{
	TileMap::Get().Load("level.txt", "map.txt");

	Mine::Get().Initialize();

	myAgent.Initialize();
	/*myAgent.SetPosition({0.0f, 0.0f});*/

	
	//int sx = X::Random(0, myTileMap.GetColumns() - 1);
	//int sy = X::Random(0, myTileMap.GetRows() - 1);

	////for testing
	//for(int i = 0; i < 1;)
	//{
	//	if (!IsBlocked(sx, sy))
	//	{
	//		startX = sx;
	//		startY = sy;
	//		i++;
	//	}
	//	else
	//	{
	//		continue;
	//	}
	//		
	//}
}

bool GameLoop(float deltaTime)
{
	TileMap::Get().Render();
	
	//DrawStartEnd(); //for tesing
	Mine::Get().Render();

	AI::Astar astar;
	
	myAgent.Update(deltaTime);
	myAgent.Render();
	

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}