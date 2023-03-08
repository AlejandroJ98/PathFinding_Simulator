#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;
void GridBasedGraph::Initialize(int columns, int rows)
{
	//TODO
	//save the columns and rows
	//resize mNodes and add nodes and neighnors
	//
	//eg
	//for(...)
	// for(...)
	//   set node column/row and add 8 nerighbors
	//   node.neighbors[East] = GetNode(x + 1, y);//
	mColumns = columns;
	mRows = rows;
	mNodes.resize((size_t)columns * rows);
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			Node* mNode = GetNode(x, y);
			mNode->column = x;
			mNode->row = y;
			mNode->neighbors[0] = GetNode(x, y - 1);
			mNode->neighbors[1] = GetNode(x, y + 1);
			mNode->neighbors[2] = GetNode(x + 1, y);
			mNode->neighbors[3] = GetNode(x - 1, y);
			mNode->neighbors[4] = GetNode(x + 1, y - 1);
			mNode->neighbors[5] = GetNode(x - 1, y - 1);
			mNode->neighbors[6] = GetNode(x + 1, y + 1);
			mNode->neighbors[7] = GetNode(x - 1, y + 1);
		}
	}
}

void GridBasedGraph::ResetSearchParams()
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			Node* mNode = GetNode(x, y);
			mNode->parent = nullptr;
			mNode->opened = false;
			mNode->closed = false;
			mNode->g = 0;
			mNode->h = 0;
		}
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	//TODO check bound, if good, return node, else return nullptr
	if (x < 0 || x > GetColumns() - 1 || y < 0 || y > GetRows() - 1)
	{
		return nullptr;
	}
	else
	{
		return &mNodes[GetIndex(x, y)];
	}
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || x > GetColumns() - 1 || y < 0 || y > GetRows() - 1)
	{
		return nullptr;
	}
	else
	{
		return &mNodes[GetIndex(x , y)];
	}
}

int GridBasedGraph::GetIndex(int x, int y)const
{
	//TODO x, y must be within (0, 0) and (colums, rows)
	return x + (y * mColumns);
}