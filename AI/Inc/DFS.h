#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	class DFS
	{
	public:
		//define IsBlocked function, that takes two integers and return a boolean
		using IsBlocked = std::function<bool(int, int)>;

		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, IsBlocked isBlocked);

		const std::list<GridBasedGraph::Node*>& GetClosedList() const { return mClosedList; }

	private:
		std::list<GridBasedGraph::Node*> mOpenList;
		std::list<GridBasedGraph::Node*> mClosedList;

	};
}