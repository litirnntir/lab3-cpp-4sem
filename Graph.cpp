#include "Graph.h"

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walk(const Vertex& start, std::function<void(const Vertex&)> action)
{
	visited[start] = true;
	action(start);
	for (auto it1 : edges(start))
	{
		Vertex next_node = it1.id2;
		if (!visited[next_node])
		{
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

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::HasVertex(const Vertex& vertex) const
{
	return (vertex.count(vertex) != 0);
};

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::AddVertex(const Vertex& v)
{
	if (!has_vertex(v))
	{
		std::map<Vertex, Edge<Vertex, Distance>> tmp;
		mapV[v] = tmp;
		return true;
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::removeVertex(const Vertex& v)
{
	if (!HasVertex(v))
	{
		return false;
	}
	mapV.erase(v);
	for (auto it = mapV.begin(); it != mapV.end(); it++)
	{
		if (it->second.count(v) != 0)
		{
			it->second.erase(v);
		}
	}
	return true;
}