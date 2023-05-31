#include "Graph.cpp"

int main()
{
	Graph<int> a;
	// ------
//	a.addVertex(1);
//	a.addVertex(2);
//	a.addVertex(3);
//	a.addVertex(4);
//	a.addEdge(1, 2, 2);
//	a.addEdge(2, 1, 2);
//	a.addEdge(2, 4, 3);
//	a.addEdge(4, 2, 3);
//	a.addEdge(1, 3, 1);
//	a.addEdge(3, 1, 1);
//	a.addEdge(3, 4, 3);
//	a.addEdge(4, 3, 3);
//	a.addEdge(4, 1, 4);
//	a.addEdge(1, 4, 4);
	// ------
	a.addVertex(1);
	a.addVertex(2);
	a.addVertex(3);
	a.addVertex(4);
	a.addVertex(5);
	a.addVertex(6);
	a.addEdge(2, 1, 1);
	a.addEdge(1, 2, 1);
	a.addEdge(1, 5, 2);
	a.addEdge(5, 1, 2);
	a.addEdge(1, 6, 5);
	a.addEdge(5, 6, 2);
	a.addEdge(6, 2, 3);
	a.addEdge(6, 3, 2);
	a.addEdge(3, 2, 4);
	a.addEdge(2, 3, 1);
	a.addEdge(6, 4, 2);
	a.addEdge(4, 5, 5);
	a.addEdge(5, 4, 2);
	a.addEdge(4, 3, 6);
	a.addEdge(3, 4, 1);
	std::vector<int> b = a.shortestPath(3, 2);
	for (auto i = b.begin(); i < b.end(); ++i)
	{
		if (i != b.end() - 1) std::cout << *i << "->";
		else std::cout << *i;
	}
	std::cout << std::endl;
	std::cout << a.findOptimal();
	std::cout << std::endl;

	std::cout <<a;
	return 0;
}