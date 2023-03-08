#include "Precompiled.h"
#include "BFS.h"

using namespace AI;

bool BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, IsBlocked isBlocked)
{
	//reset enerything
	graph.ResetSearchParams();
	mOpenList.clear();
	mClosedList.clear();

	//Add start node to open list
	auto node = graph.GetNode(startX, startY);
	auto End = graph.GetNode(endX, endY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;
	
	//while end node not reached && open list isn't empty
	//select node N from open list
	//if node is end
	//        found = true
	//else expand node N
	//      if expand node isn't in open or closed lists:
	//          add expanded node to open list, set parent
	//add node N to closed list
	//mClosedList.push_back(node)
	//node->closed = true;
	while(!found && !mOpenList.empty())
	{
		auto N = mOpenList.front();
		mOpenList.pop_front();
		
		if (N == End)
		{
			found = true;
		}
		else
		{
			for (auto neighbor : N->neighbors)
			{
				if (neighbor == nullptr || isBlocked(neighbor->column, neighbor->row))
				{
					continue;
				}
				if(!neighbor->opened && !neighbor->closed)
				{
					mOpenList.push_back(neighbor);
					neighbor->opened = true;
					neighbor->parent = N;
				}
			}
		}
		mClosedList.push_back(N);
		N->closed = true;
	}
	return found;
}

