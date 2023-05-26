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
template<typename Vertex, typename Distance>
std::ostream& operator<<(std::ostream& out, Graph<Vertex> graph)
{
	for (auto it = graph.mapV.begin(); it != graph.mapV.end(); ++it)
	{
		out << std::endl << '[' << it->first << ']' << ':' << it->second;
	}
	return out;
}