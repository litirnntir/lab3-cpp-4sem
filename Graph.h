#ifndef LAB3_CPP_4SEM__GRAPH_H_
#define LAB3_CPP_4SEM__GRAPH_H_

#include <iostream>
#include <map>
#include <map>
#include <vector>
#include <queue>

template<typename tVertex, typename tDistance = double>

// Структура ребра
struct Edge
{
	tVertex from;
	tVertex to;
	tDistance distance;
	Edge(tVertex from = 0, tVertex to = 0, tDistance distance = 0) : from(from), to(to), distance(distance)
	{
	}
	friend std::ostream& operator<<(std::ostream& out, const std::map<int, Edge<tVertex>>& map)
	{
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			out << it->second;
		}
		return out;
	}
	friend std::ostream& operator<<(std::ostream& out, const Edge<tVertex>& edge)
	{
		out << "->(" << edge.from << ", " << edge.to << "; " << edge.distance << ")";
		return out;
	}
};
// Шаблон для строк
template<>
struct Edge<std::string, double>
{
	std::string from;
	std::string to;
	double distance;
	Edge(std::string from = "", std::string to = "", double distance_ = 0)
		: from(std::move(from)), to(std::move(to)), distance(distance_)
	{
	}
	friend std::ostream& operator<<(std::ostream& out, const Edge<std::string>& edge)
	{
		out << "->(" << edge.from << ", " << edge.to << "; " << edge.distance << ")";
		return out;
	}
	friend std::ostream& operator<<(std::ostream& out, const std::map<int, Edge<std::string>>& map)
	{
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			out << it->second;
		}
		return out;
	}
};

template<typename Vertex, typename Distance = double>
class Graph
{
 public:

	std::map<Vertex, std::map<Vertex, Edge<Vertex, Distance>>> mapV;
	std::map<Vertex, bool> visited;

	//проверка-добавление-удаление вершин
	bool hasVertex(const Vertex& v) const;
	bool addVertex(const Vertex& v);
	bool removeVertex(const Vertex& v);
	std::vector<Vertex> vertices() const;

	//проверка-добавление-удаление ребер
	bool addEdge(const Vertex& from, const Vertex& to,
		const Distance& d);
	bool removeEdge(const Vertex& from, const Vertex& to);
	bool removeEdge(const Edge<Vertex, Distance>& edge); //c учетом расстояния
	bool hasEdge(const Vertex& from, const Vertex& to) const;
	bool hasEdge(const Edge<Vertex, Distance>& edge); //c учетом расстояния в Edge

	//получение всех ребер, выходящих из вершины
	std::vector<Edge<Vertex, Distance>> edges(const Vertex& vertex);

	size_t order() const; //порядок
	size_t degree() const; //степень


	//поиск кратчайшего пути
	std::vector<Vertex> shortestPath(const Vertex& from,
		const Vertex& to);

	//обход
	void walk(const Vertex& start, std::function<void(const Vertex&)> action);

	friend std::ostream& operator<<(std::ostream& out, Graph<Vertex> graph);

	//задача
	Vertex findOptimal();
};

#endif //LAB3_CPP_4SEM__GRAPH_H_