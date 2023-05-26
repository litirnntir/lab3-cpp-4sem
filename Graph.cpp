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
bool Graph<Vertex, Distance>::removeEdge(const Edge<Vertex, Distance>& edge)
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
bool Graph<Vertex, Distance>::hasEdge(const Edge<Vertex, Distance>& edge)
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

template<typename Vertex, typename Distance>
std::vector<Edge<Vertex, Distance>> Graph<Vertex, Distance>::edges(const Vertex& vertex)
{
	std::vector<Edge<Vertex, Distance>> edgesMap;
	if (has_vertex(vertex))
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
std::vector<Edge<Vertex, Distance>> Graph<Vertex, Distance>::shortestPath(const Vertex& from, const Vertex& to) const
{
	std::map<Vertex, Distance> distances;
	std::map<Vertex, Vertex> prev;
	for (auto i : vertices())
	{
		distances[i] = INT_MAX;
	}
	std::queue<std::pair<Distance, Vertex>> pq;
	distances[from] = 0;
	pq.push({ 0, from });
	while (!pq.empty())
	{
		Distance dist = pq.front().first;
		Vertex vertex = pq.front().second;
		pq.pop();
		if (dist > distances[vertex])
		{
			continue;
		}
		for (auto i : edges(vertex))
		{
			double newD;
			newD = dist + i.dist;
			if (newD < distances[i.to])
			{
				distances[i.to] = newD;
				prev[i.to] = vertex;
				pq.push(make_pair(newD, i.to));
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
	std::map<Vertex, Distance> mapOfDistance;
	for (auto it1 = mapV.begin(); it1 != mapV.end(); it1++)
	{
		int infCount = 0;
		int okCount = mapV.size() / 4;
		Distance sum = 0;
		for (auto it2 = mapV.begin(); it2 != mapV.end(); it2++)
		{
			if (it1 == it2)
			{
				continue;
			}
			std::vector<Edge<Vertex, Distance>> tmp = shortestPath(it1->first, it2->first);
			if (tmp.size() == 0)
			{
				mapOfDistance[it1->first] = std::numeric_limits<Distance>::max();
				break;
			}
			for (auto i : tmp)
			{
				sum += i.dist;
			}
		}
		if (mapOfDistance[it1->first] != std::numeric_limits<Distance>::max())
		{
			mapOfDistance[it1->first] = sum;
		}
	}
	Vertex vertexWithMinDist;
	Distance minDist = std::numeric_limits<Distance>::max();
	for (auto it = mapOfDistance.begin(); it != mapOfDistance.end(); it++)
	{
		Distance dist = it->second;
		if (dist < minDist)
		{
			minDist = dist;
			vertexWithMinDist = it->first;
		}
	}
	return vertexWithMinDist;
}
