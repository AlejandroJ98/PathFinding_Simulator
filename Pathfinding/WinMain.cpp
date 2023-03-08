#include <XEngine.h>
#include "TileMap.h"
#include <AI.h>
#include <ImGui/Inc/imgui.h>

AI::GridBasedGraph myGraph;
TileMap myTileMap;

int startX = 0;
int startY = 0;
int endX = 0;
int endY = 0;

bool drawGraph = false;

std::list<AI::GridBasedGraph::Node*> path;
std::list<AI::GridBasedGraph::Node*> closedList;

bool IsBlocked(int column, int row)
{
	return myTileMap.IsBlocked(column, row);
}

float GetCost(int column, int row)
{
	return myTileMap.GetTraversalCost(column, row);
}

float GetHeuristic(int fromX, int fromY, int toX, int toY)
{
	X::Math::Vector2 fromPos( fromX, fromY );
	X::Math::Vector2 toPos(toX, toY);
	return X::Math::Distance(fromPos, toPos);
}

X::Math::Vector2 GetPixelPosition(int column, int row)
{
	return{
		(column + 0.5f)*myTileMap.GetTileWidth(),
		(row + 0.5f)*myTileMap.GetTileHeight()
	};
}

void ExtractPath()
{
	//start from the end node
	auto node = myGraph.GetNode(endX, endY);

	//jump backwards until we hit a node with no parent
	path.clear();
	while (node != nullptr)
	{
		path.push_front(node);
		node = node->parent;
	}
}

void DrawGraph( const AI::GridBasedGraph& graph)
{
	//TODO
	//- Get each node of the graph and draw lines from the node to each neighbors
	for (int y = 0; y < graph.GetRows(); ++y)
	{
		for (int x = 0; x < graph.GetColumns(); ++x)
		{
			auto node = graph.GetNode(x, y);
			for (auto neighbor : node->neighbors)
			{
				if (neighbor)
				{
					X::Math::Vector2 a(node->column * 32.0f, node->row * 32.0f);
					X::Math::Vector2 b(neighbor->column * 32.0f, neighbor->row * 32.0f);
					X::Math::Vector2 offset(16.0f, 16.0f);
					X::DrawScreenLine(a+offset, b+offset, X::Colors::Black);
				}
			}
		}
	}
}

void DrawClosedList()
{
	//TODO
	// - To draw the closed list, for each node in the list, draw a line between the node and it's parent
	
	for (auto it = closedList.begin(); it != closedList.end(); it++)
	{
		auto node = *it;
		if (node->parent != nullptr)
		{
			X::DrawScreenLine(GetPixelPosition(node->column, node->row), GetPixelPosition(node->parent->column, node->parent->row), X::Colors::White);
		}
	}
}

void DrawPath()
{
	//TODO
	// - To draw the path, for each node in the list, draw a line between the node and the parent

		for (auto it = path.begin(); it != path.end(); it++)
		{
			auto node = *it;
			if (node->parent != nullptr)
			{
				X::DrawScreenLine(GetPixelPosition(node->column, node->row), GetPixelPosition(node->parent->column, node->parent->row), X::Colors::Blue);
			}
		}
}

void DrawStartEnd()
{
	X::DrawScreenCircle(GetPixelPosition(startX, startY), 10.0f, X::Colors::Magenta);
	X::DrawScreenCircle(GetPixelPosition(endX, endY), 10.0f, X::Colors::Red);
}

void DrawUI()
{
	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderInt("Start X", &startX, 0, myTileMap.GetColumns() - 1);
	ImGui::SliderInt("Start Y", &startY, 0, myTileMap.GetRows() - 1);
	ImGui::SliderInt("End X", &endX, 0, myTileMap.GetColumns() - 1);
	ImGui::SliderInt("End Y", &endY, 0, myTileMap.GetRows() - 1);
	ImGui::Checkbox("draw Graph", &drawGraph);
	
	if (ImGui::Button("Run BFS"))
	{
		AI::BFS bfs;
		if (bfs.Run(myGraph, startX, startY, endX, endY, IsBlocked))
		{
			closedList = bfs.GetClosedList();
			ExtractPath();
		}
	}
	if (ImGui::Button("Run DFS"))
	{
		AI::DFS dfs;
		if (dfs.Run(myGraph, startX, startY, endX, endY, IsBlocked))
		{
			closedList = dfs.GetClosedList();
			ExtractPath();
		}
	}
	if (ImGui::Button("Run Dijkstra"))
	{
		AI::Dijkstra dijk;
		if (dijk.Run(myGraph, startX, startY, endX, endY, IsBlocked, GetCost))
		{
			closedList = dijk.GetClosedList();
			ExtractPath();
		}
	}
	if (ImGui::Button("Run Astar"))
	{
		AI::Astar astar;
		if (astar.Run(myGraph, startX, startY, endX, endY, IsBlocked, GetCost, GetHeuristic))
		{
			closedList = astar.GetClosedList();
			ExtractPath();
		}
	}
	ImGui::End();
}

void GameInit()
{
	myTileMap.Load("level.txt", "map.txt");
	
	//initialize graph to matching size as the map
	myGraph.Initialize(myTileMap.GetColumns(), myTileMap.GetRows());
}

bool GameLoop(float deltaTime)
{
	myTileMap.Render();
	if (drawGraph)
		DrawGraph(myGraph);
	//DrawGraph(myGraph);
	DrawClosedList();
	DrawPath();
	DrawStartEnd();
	DrawUI();

	//X::DrawScreenLine({ 100,100 }, { 500,200 }, X::Colors::Gainsboro);

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