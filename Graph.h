#ifndef LAB3_CPP_4SEM__GRAPH_H_
#define LAB3_CPP_4SEM__GRAPH_H_

#include <iostream>;

template<typename Vertex, typename Distance = double>
class Graph{
 public:
	struct Edge{/*...*/};


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
	bool has_edge (const Edge& e); //c учетом расстояния в Edge

	//получение всех ребер, выходящих из вершины
	std::vector<Edge> edges(const Vertex& vertex);

	size_t order() const; //порядок
	size_t degree() const; //степень


	//поиск кратчайшего пути
	std::vector<Edge> shortest_path(const Vertex& from,
		const Vertex& to) const;
	//обход
	std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};


#endif //LAB3_CPP_4SEM__GRAPH_H_
