#include "Graph.h"

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walk(const Vertex& start, std::function<void(const Vertex&)> action)
{
	visited[start] = true;
	action(start);
	for (auto it1 : edges(start)) {
		Vertex next_node = it1.id2;
		if (!visited[next_node]) {
			walk_(next_node, action);
		}
	}
}