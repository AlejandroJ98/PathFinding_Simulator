#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	class Dijkstra
	{
	public:
		//define IsBlocked function, that takes two integers and return a boolean
		using IsBlocked = std::function<bool(int, int)>;
		using GetCost = std::function<float(int, int)>;
		// TODO - Update to use this version that makes diagonals more expensive
		//using GetCost = std::function<float(int, int, int, int)>;

		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, 
			IsBlocked isBlocked, GetCost getcost);

		const std::list<GridBasedGraph::Node*>& GetClosedList() const { return mClosedList; }

	private:
		std::list<GridBasedGraph::Node*> mOpenList;
		std::list<GridBasedGraph::Node*> mClosedList;

	};
}