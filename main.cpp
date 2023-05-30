#include "Graph.cpp"

int main()
{
	Graph<int> a;
	a.addVertex(1);
	a.addVertex(2);
	a.addVertex(3);
	a.addVertex(4);
	a.addEdge(1, 2, 2);
	a.addEdge(2, 1, 2);
	a.addEdge(2, 4, 3);
	a.addEdge(4, 2, 3);
	a.addEdge(1, 3, 1);
	a.addEdge(3, 1, 1);
	a.addEdge(3, 4, 3);
	a.addEdge(4, 3, 3);
	a.addEdge(4, 1, 4);
	a.addEdge(1, 4, 4);
	std::vector<int> b = a.shortestPath(3, 2);
	for (auto i = b.begin(); i < b.end(); ++i)
	{
		if (i != b.end()-1) std::cout << *i << "->";
		else std::cout << *i;
	}
	std::cout << std::endl;

	//----------
//	a.addEdge(1,2,1);
//	a.addEdge(2,1,1);
//	a.addEdge(1,3,1);
//	a.addEdge(3,1,1);
//	a.addEdge(1,4,1);
//	a.addEdge(4,1,1);
//	a.addEdge(2,3,2);
//	a.addEdge(3,2,2);
//	a.addEdge(3,4,2);
//	a.addEdge(4,2,2);
//	a.addEdge(2,4,2);
//	a.addEdge(4,2,2);
//--------
	std::cout << a.findOptimal();
	return 0;
}