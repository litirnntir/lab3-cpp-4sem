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
bool Graph<Vertex, Distance>::hasEdge(const Vertex& from, const Vertex& to) const
{
	if (hasVertex(from) && hasVertex(to))
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
	if (hasVertex(edge.from) && hasVertex(edge.to))
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
			newD = dist + i.distance;
			if (newD < distances[i.to])
			{
				distances[i.to] = newD;
				prev[i.to] = vertex;
				pq.push(std::make_pair(newD, i.to));
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
//template<typename Vertex, typename Distance>
//Vertex Graph<Vertex, Distance>::findOptimal()
//{
//	return nullptr;
//}

template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::findOptimal()
{
	// Инициализируем константу INF
	const Distance INF = std::numeric_limits<Distance>::max();

	// Создаем копию графа для вычисления расстояний
	std::map<Vertex, std::map<Vertex, Distance>> dist;
	for (auto&[v1, edges] : mapV)
	{
		for (auto&[v2, edge] : edges)
		{
			dist[v1][v2] = edge.distance;
		}
	}

	// Инициализируем диагональные элементы расстояний нулями
	for (auto&[k, _] : dist)
	{
		dist[k][k] = 0;
	}

	// Применяем алгоритм Флойда-Уоршелла для вычисления кратчайших расстояний между всеми вершинами
	for (auto&[k, _] : dist)
	{
		for (auto&[i, _] : dist)
		{
			for (auto&[j, _] : dist)
			{
				if (dist[i][k] != INF && dist[k][j] != INF)
				{
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}

	// Находим вершину с наименьшим максимальным расстоянием до других вершин
	Distance ans = INF;
	Vertex res;
	for (auto&[v, d] : dist)
	{
		Distance maxDist = 0;
		for (auto&[_, dist] : d)
		{
			maxDist = std::max(maxDist, dist);
		}
		if (maxDist < ans)
		{
			ans = maxDist;
			res = v;
		}
	}

	// Возвращаем результат
	return res;
}


