#include "Precompiled.h"
#include "Astar.h"

using namespace AI;


//namespace
//{
//	struct sortO
//	{
//		bool operator()(AI::GridBasedGraph::Node* N1, AI::GridBasedGraph::Node* N2)
//		{
//			return N1->g < N2->g;
//		}
//	};
//}
bool Astar::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, IsBlocked isBlocked, GetCost getcost, GetHeuristic getHeuristic)
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

	while (!found && !mOpenList.empty())
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
				if (neighbor == nullptr || neighbor->opened || isBlocked(neighbor->column, neighbor->row))
				{
					continue;
				}

				if (!neighbor->opened)
				{
					mOpenList.push_back(neighbor);
					neighbor->opened = true;
					neighbor->parent = N;
					neighbor->g = N->g + getcost(neighbor->column, neighbor->row);
					neighbor->h = getHeuristic(neighbor->column, neighbor->row, endX, endY);
					
					mOpenList.sort([](auto a, auto b)
						{
							return (a->g + a->h) < (b->g + b->h);
						});
					//mOpenList.sort(sortO());
				}
			}
			//sort openlist by g
			//
			//           add expanded node to open list, set parent to node N
			// add node N to closed list
		}
		mClosedList.push_back(N);

		N->closed = true;
	}
	return found;
}

