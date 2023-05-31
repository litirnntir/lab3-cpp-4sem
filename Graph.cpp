#include "Graph.h"

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

template<typename Vertex, typename Distance = double>
void Print(const Vertex& val)
{
	std::cout << val << '|';
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walk_(const Vertex& startVertex, std::function<void(const Vertex&)> action)
{
	visited[startVertex] = true;
	action(startVertex);
	for (auto it1 : edges(startVertex))
	{
		Vertex next_node = it1.to;
		if (!visited[next_node])
		{
			walk_(next_node, action);
		}
	}

}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::init()
{
	for (auto i : vertices())
	{
		visited[i] = false;
	}
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walk(const Vertex& startVertex, std::function<void(const Vertex&)> action)
{
	init();
	walk_(startVertex, action);
	for (auto& node : visited)
	{
		if (!node.second)
		{
			walk_(node.first, action);
		}
	}

}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::hasVertex(const Vertex& v) const
{
	for (const auto& vert : mapV)
	{
		if (v == vert.first) return true;
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::addVertex(const Vertex& v)
{
	if (!hasVertex(v))
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
	if (!hasVertex(v))
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
bool Graph<Vertex, Distance>::addEdge(const Vertex& from, const Vertex& to, const Distance& d)
{
	if (hasVertex(from) && hasVertex(to))
	{
		Edge<Vertex, Distance> tmp(from, to, d);
		if (!hasEdge(tmp))
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
		if (hasEdge(from, to))
		{
			mapV[from].erase(to);
			return true;
		}
		return false;
	}
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::removeEdge(const Edge<Vertex, Distance>& edge)
{
	if (hasEdge(edge))
	{
		mapV[edge.from].erase(edge.to);
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::hasEdge(const Vertex& from, const Vertex& to)
{
	if (hasVertex(from) && hasVertex(to))
	{
		for (auto it : edges(from))
		{
			if (it.to == to) return true;
		}
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::hasEdge(const Edge<Vertex>& e)
{
	if (hasVertex(e.from) && hasVertex(e.to))
	{
		for (auto it : edges(e.from))
		{
			if (it.to == e.to && it.distance == e.distance) return true;
		}
	}
	return false;
}

template<typename Vertex, typename Distance>
std::vector<Edge<Vertex, Distance>> Graph<Vertex, Distance>::edges(const Vertex& vertex)
{
	std::vector<Edge<Vertex, Distance>> edgesMap;
	if (hasVertex(vertex))
	{
		for (auto i = mapV[vertex].begin(); i != mapV[vertex].end(); i++)
		{
			edgesMap.push_back(i->second);
		}
		return edgesMap;
	}
	return edgesMap;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree() const
{
	int maxSize = -1;
	for (auto it = mapV.begin(); it != mapV.end(); it++)
	{
		std::vector<Edge<Vertex, Distance>> edgesTmp = edges(it->first);
		int size = edgesTmp.size();
		if (size > maxSize)
		{
			maxSize = size;
		}
	}
	return maxSize;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const
{
	return mapV.size();
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::shortestPath(const Vertex& from, const Vertex& to)
{
	if (!hasVertex(from) || !hasVertex(to))
	{
		std::vector<Vertex> a;
		return a;
	}
	std::map<Vertex, Distance> dist;
	std::map<Vertex, Vertex> prev;

	for (auto& vertex : mapV)
	{
		dist[vertex.first] = std::numeric_limits<Distance>::max();
	}
	dist[from] = 0;

	for (int i = 0; i < mapV.size() - 1; i++)
	{
		for (auto& vertex : mapV)
		{
			for (auto& edge : vertex.second)
			{
				if (dist[vertex.first] != std::numeric_limits<Distance>::max()
					&& dist[vertex.first] + edge.second.distance < dist[edge.second.to])
				{
					dist[edge.second.to] = dist[vertex.first] + edge.second.distance;
					prev[edge.second.to] = vertex.first;
				}
			}
		}
	}

	for (auto& vertex : mapV)
	{
		for (auto& edge : vertex.second)
		{
			if (dist[vertex.first] != std::numeric_limits<Distance>::max()
				&& dist[vertex.first] + edge.second.distance < dist[edge.second.to])
			{
				throw std::runtime_error("Negative cycle detected");
			}
		}
	}

	std::vector<Vertex> path;
	Vertex current = to;
	while (current != from)
	{
		path.push_back(current);
		current = prev[current];
	}
	path.push_back(from);
	std::reverse(path.begin(), path.end());
	return path;
}

template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::findOptimal()
{
	std::map<Vertex, Distance> maxes;
	Vertex id;
	Distance min;
	for (auto i : vertices())
	{
		Distance max;
		for (auto j : vertices())
		{
			if (i == j) continue;
			else
			{
				Distance sum = 0;
				std::vector<Vertex> path = shortestPath(j, i);
				for (auto k = path.begin(); k < path.end() - 1; k++)
				{
					sum = sum + mapV[*k][*(k + 1)].distance;
				}
				if (sum > max || !max) max = sum;
			}
		}
		maxes.insert(std::make_pair(i, max));
		min = maxes[i];
	}
	for (auto i : vertices())
	{
		if (maxes[i] < min)
		{
			min = maxes[i];
			id = i;
		}
	}
	return id;
}


