#ifndef LAB3_CPP_4SEM__GRAPH_H_
#define LAB3_CPP_4SEM__GRAPH_H_

#include <iostream>
#include <map>
#include <utility>

template<typename Vertex, typename Distance = double>
class Graph
{
 public:
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

	// Для обхода
	std::map<Vertex, std::map<int,Edge<Vertex>>> mapV;
	std::map<Vertex, bool>visited;

	//проверка-добавление-удаление вершин
	bool has_vertex(const Vertex& v) const;
	void add_vertex(const Vertex& v);
	bool remove_vertex(const Vertex& v);
	std::vector<Vertex> vertices() const;

	//проверка-добавление-удаление ребер
	void add_edge(const Vertex& from, const Vertex& to,
		const Distance& d);
	bool remove_edge(const Vertex& from, const Vertex& to);
	bool remove_edge(const Edge& e); //c учетом расстояния
	bool has_edge(const Vertex& from, const Vertex& to) const;
	bool has_edge(const Edge& e); //c учетом расстояния в Edge

	//получение всех ребер, выходящих из вершины
	std::vector<Edge> edges(const Vertex& vertex);

	size_t order() const; //порядок
	size_t degree() const; //степень


	//поиск кратчайшего пути
	std::vector<Edge> shortest_path(const Vertex& from,
		const Vertex& to) const;

	//обход
	void walk(const Vertex& start, std::function<void(const Vertex&)> action);
	friend std::ostream& operator<< (std::ostream& out, Graph<Vertex>graph);
};

#endif //LAB3_CPP_4SEM__GRAPH_H_
