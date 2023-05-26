#include "Graph.h"

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walk(const Vertex& start, std::function<void(const Vertex&)> action)
{
	visited[start] = true;
	action(start);
	for (auto it1 : edges(start))
	{
		Vertex next_node = it1.to;
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

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::vertices() const
{
	std::vector<Vertex> vertexMap;
	for (auto i = mapV.begin(); i != mapV.end(); i++)
	{
		vertexMap.push_back(i->first);
	}
	return vertexMap;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::addEdge(const Vertex& from, const Vertex& to, const Distance& d)
{
	if (has_vertex(from) && has_vertex(to))
	{
		Edge<Vertex, Distance> tmp(from, to, d);
		if (!has_edge(tmp))
		{
			mapV[from][to] = tmp;
			return true;
		}
		return false;
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::removeEdge(const Vertex& from, const Vertex& to)
{
	{
		if (has_edge(from, to))
		{
			mapV[from].erase(to);
			return true;
		}
		return false;
	}
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::removeEdge(const Graph::Edge<Vertex, Distance>& edge)
{
	if (has_edge(edge))
	{
		mapV[edge.from].erase(edge.to);
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::hasEdge(const Vertex& from, const Vertex& to) const
{
	if (has_vertex(from) && has_vertex(to))
	{
		if (mapV[from].count(to) != 0)//graph[from].find(to) != graph[from].end()
		{
			return true;
		}
	}
	return false;
}
template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::hasEdge(const Graph::Edge<Vertex, Distance>& edge)
{
	if (has_vertex(edge.from) && has_vertex(edge.to))
	{
		if (mapV[edge.from].find(edge.to) != mapV[edge.from].end())
		{
			if (mapV[edge.from][edge.to].distance == edge.distance)
			{
				return true;
			}
		}
	}
	return false;
}
