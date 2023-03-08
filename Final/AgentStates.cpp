#include "AgentStates.h"
#include "TileMap.h"
#include "Mine.h"



namespace
{
	AI::GridBasedGraph myGraph;
	std::list<AI::GridBasedGraph::Node*> nodePath;
	std::list<AI::GridBasedGraph::Node*> closedList;
	


	bool IsBlocked(int column, int row)
	{
		return TileMap::Get().IsBlocked(column, row);
	}

	float GetCost(int column, int row)
	{
		return TileMap::Get().GetTraversalCost(column, row);
	}

	float GetHeuristic(int fromX, int fromY, int toX, int toY)
	{
		X::Math::Vector2 fromPos(fromX, fromY);
		X::Math::Vector2 toPos(toX, toY);
		return X::Math::Distance(fromPos, toPos);
	}

	X::Math::Vector2 GetPixelPosition(int column, int row)
	{
		return{
			(column + 0.5f) * TileMap::Get().GetTileWidth(),
			(row + 0.5f) * TileMap::Get().GetTileHeight()
		};
	}

	X::Math::Vector2 GetPosition(AI::GridBasedGraph::Node* node)
	{
		return GetPixelPosition(node->column, node->row);
	}
}

//move state
void MoveState::Enter(Agent& agent)
{
	agent.SetTextureId(X::LoadTexture("scv_05.png"));
	mWaitTime = 0.0f;
}

void MoveState::Update(Agent& agent, float deltaTime)
{
	mWaitTime += deltaTime;
	if (mWaitTime < 1.0f)
		return;

	// (Task)
	// Move
	if (agent.Path.size() != 0)
	{
		auto FS = agent.Path.begin();//assign first step
		agent.Path.erase(FS);//delete FS
		if (agent.Path.size() != 0)
		{
			auto NS = GetPosition(agent.Path.front());//get next step
			agent.SetPosition(NS);//set to next step
			mWaitTime = 0.0f;
		}
	}
	else
	{
		agent.ChangeState("MoveBackState");
	}
}

void MoveState::Exit(Agent& agent)
{

}


//search state
void SearchState::Enter(Agent& agent)
{
}

void SearchState::Update(Agent& agent, float deltaTime)
{
	bool foundPath = false;

	int startX = agent.GetPosition().x / 32.0f;
	int startY = agent.GetPosition().y / 32.0f;
	int endX = Mine::Get().mPosition.x / 32.0f;
	int endY = Mine::Get().mPosition.y / 32.0f;

	
	myGraph.Initialize(TileMap::Get().GetColumns(), TileMap::Get().GetRows());
		
	AI::Astar astar;
	if (astar.Run(myGraph, startX, startY, endX, endY, IsBlocked, GetCost, GetHeuristic))
	{
		foundPath = true;
		closedList = astar.GetClosedList();
	}

	/*AI::BFS bfs;
	if (bfs.Run(myGraph, startX, startY, endX, endY, IsBlocked))
	{
		foundPath = true;
		closedList = bfs.GetClosedList();
	}*/

	if (foundPath)
	{
		auto N = myGraph.GetNode(endX, endY);
		while (N != nullptr)
		{
			nodePath.push_back(N);
			N = N->parent;
		}

		std::reverse(nodePath.begin(), nodePath.end());//change the order
		agent.Path = nodePath;//assign agent path to the search path
		agent.ChangeState("MoveState");
	}
}

void SearchState::Exit(Agent& agent)
{
}




//pickup state
//void PickUpState::Enter(Agent& agent)
//{
//}
//
//void PickUpState::Update(Agent& agent, float deltaTime)
//{
//}
//
//void PickUpState::Exit(Agent& agent)
//{
//}





//move back state
void MoveBack::Enter(Agent& agent)
{
}

void MoveBack::Update(Agent& agent, float deltaTime)
{


}

void MoveBack::Exit(Agent& agent)
{
}
