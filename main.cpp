#include "Graph.cpp"

#include <iostream>
#include <memory>
#include <vector>
#include <cfloat>
#include "Graph.h"

int checkIsInt()
{
	int number;
	while (!(std::cin >> number) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect number, input again: ";
	}
	return number;
}

int checkMenu4()
{
	int number;
	while (!(std::cin >> number) || (std::cin.peek() != '\n') || number > 5 || number < 1)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect number, input again: ";
	}
	return number;
}

int checkMenu10()
{
	int number;
	while (!(std::cin >> number) || (std::cin.peek() != '\n') || number > 10 || number < 1)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect number, input again: ";
	}
	return number;
}

double Number()
{
	double tmp;
	char string[24];
	bool flag = false;
	while (!flag)
	{
		bool exit = true;
		std::cin >> string;
		char* end = string;
		tmp = strtod(string, &end);
		if (end == string)
		{
			continue;
		}
		if ((tmp == DBL_MAX || tmp == DBL_MIN) && errno == ERANGE)
		{
			continue;
		}
		while (*end)
		{
			if ((*end != ' ') && (*end != '\n'))
			{
				exit = false;
				break;
			}
			end++;
		}
		if (exit)
		{
			flag = true;
		}
		else
		{
			flag = false;
			printf("\nIncorrect number\n");
		}
	}
	return tmp;
}

void menu()
{
	std::cout << "1. Create a graph" << std::endl;
	std::cout << "2. Find optimal (Task №2)" << std::endl;
	std::cout << "3. Modified walk function signature" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "choice: ";
}

void menu1()
{
	std::cout << "Choose data type for the vertices:" << std::endl;
	std::cout << "1. int" << std::endl;
	std::cout << "2. double" << std::endl;
	std::cout << "3. string" << std::endl;
	std::cout << "4. back" << std::endl;
	std::cout << "choice: ";
}

void menu11()
{
	std::cout << "1. Add vertex" << std::endl;
	std::cout << "2. Remove vertex" << std::endl;
	std::cout << "3. Add edge" << std::endl;
	std::cout << "4. Exist edge" << std::endl;
	std::cout << "5. Remove edge weight" << std::endl;
	std::cout << "6. Remove edge weightless" << std::endl;
	std::cout << "7. Shortest path" << std::endl;
	std::cout << "8. DFS" << std::endl;
	std::cout << "9. Print graph" << std::endl;
	std::cout << "10. Back" << std::endl;
	std::cout << "choice: ";
}

int main()
{
	int choice;
	bool exit = false;
	while (!exit)
	{
		menu();
		choice = checkMenu4();
		switch (choice)
		{
		case (1):
		{
			int choice1;
			bool exit1 = false;
			while (!exit1)
			{
				menu1();
				choice1 = checkMenu4();
				switch (choice1)
				{
				case (1):
				{
					int choiceM;
					bool exitM= false;
					Graph<int> graph;
					while (!exitM)
					{
						menu11();
						choiceM = checkMenu10();
						switch (choiceM)
						{
						case (1):
						{
							std::cout << "Enter vertex: ";
							int vertex = checkIsInt();
							if (!graph.addVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " already exist";
							}
							else
							{
								std::cout << "Vertex added" << std::endl;
							}
							std::cout << graph;
							break;
						}
						case (2):
						{
							std::cout << "Enter vertex: ";
							int vertex = checkIsInt();
							if (!graph.removeVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " doesn't exist";
							}
							else
							{
								std::cout << "Vertex erased" << std::endl;
							}
							break;
						}
						case (3):
						{
							std::cout << "Enter first vertex: ";
							int vertex1 = checkIsInt();
							std::cout << "Enter second vertex: ";
							int vertex2 = checkIsInt();
							std::cout << "Enter weight of edge: ";
							double weight = checkIsInt();
							if (!graph.addEdge(vertex1, vertex2, weight))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")_"
										  << weight << " already exist or doesn't exist vertex1: " << vertex1
										  << " or vertex2: " << vertex2 << std::endl;
							}
							else
							{
								std::cout << "Edge added" << std::endl;
							}
							break;
						}
						case (4):
						{
							std::cout << "Enter first vertex: ";
							int vertex1 = checkIsInt();
							std::cout << "Enter second vertex: ";
							int vertex2 = checkIsInt();
							if (!graph.hasEdge(vertex1, vertex2))
							{
								std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
							}
							else
							{
								std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
							}
							break;
						}
						case (5):
						{
							std::cout << "Enter first vertex: ";
							int vertex1 = checkIsInt();
							std::cout << "Enter second vertex: ";
							int vertex2 = checkIsInt();
							std::cout << "Enter weight of edge: ";
							double weight = checkIsInt();
							Edge<int> tmp(vertex1, vertex2, weight);
							if (!graph.removeEdge(tmp))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")_"
										  << weight << " doesn't exist";
							}
							else
							{
								std::cout << "Edge erased" << std::endl;
							}
							break;
						}
						case (6):
						{
							std::cout << "Enter first vertex: ";
							int vertex1 = checkIsInt();
							std::cout << "Enter second vertex: ";
							int vertex2 = checkIsInt();
							if (!graph.removeEdge(vertex1, vertex2))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")"
										  << " doesn't exist";
							}
							else
							{
								std::cout << "Edge erased" << std::endl;
							}
							break;
						}
						case (7):
						{
							std::cout << "Enter first vertex: ";
							int vertex1 = checkIsInt();
							std::cout << "Enter second vertex: ";
							int vertex2 = checkIsInt();
							std::vector<int> tmp = graph.shortestPath(vertex1, vertex2);
							if (tmp.empty())
							{
								std::cout << "Shortest path doesn't exist" << std::endl;
							}
							else
							{
								std::cout << std::endl << "Shortest path: ";
								for (auto i : tmp)
								{
									std::cout << i << " ";
								}
							}
							std::cout << std::endl;
							break;
						}
						case (8):
						{
							std::cout << "Enter vertex: ";
							int vertex = checkIsInt();
							if (!graph.hasVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " doesn't exist";
							}
							else
							{
								std::cout << "DFS: ";
								graph.walk(vertex, Print<int>);
							}
							std::cout << std::endl;
							break;
						}
						case (9):
						{
							std::cout << graph;
							break;
						}
						case (10):
						{
							std::cout << "Exit!" << std::endl;
							exitM= true;
							break;
						}
						default:
							std::cout << "Error, try again" << std::endl;
							break;
						}
					}
					break;
				}
				case (2):
				{
					int choiceM;
					bool exitM= false;
					Graph<double> graph;
					while (!exitM)
					{
						menu11();
						choiceM = checkMenu10();
						switch (choiceM)
						{
						case (1):
						{
							std::cout << "Enter vertex: ";
							double vertex = checkIsInt();
							if (!graph.addVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " already exist";
							}
							else
							{
								std::cout << "Vertex added" << std::endl;
							}
							std::cout << graph;
							break;
						}
						case (2):
						{
							std::cout << "Enter vertex: ";
							double vertex = Number();
							if (!graph.removeVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " doesn't exist";
							}
							else
							{
								std::cout << "Vertex erased" << std::endl;
							}
							break;
						}
						case (3):
						{
							std::cout << "Enter first vertex: ";
							double vertex1 = Number();
							std::cout << "Enter second vertex: ";
							double vertex2 = Number();
							std::cout << "Enter weight of edge: ";
							double weight = Number();
							if (!graph.addEdge(vertex1, vertex2, weight))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")_"
										  << weight << " already exist or doesn't exist vertex1: " << vertex1
										  << " or vertex2: " << vertex2 << std::endl;
							}
							else
							{
								std::cout << "Edge added" << std::endl;
							}
							break;
						}
						case (4):
						{
							std::cout << "Enter first vertex: ";
							double vertex1 = Number();
							std::cout << "Enter second vertex: ";
							double vertex2 = Number();
							if (!graph.hasEdge(vertex1, vertex2))
							{
								std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
							}
							else
							{
								std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
							}
							break;
						}
						case (5):
						{
							std::cout << "Enter first vertex: ";
							double vertex1 = Number();
							std::cout << "Enter second vertex: ";
							double vertex2 = Number();
							std::cout << "Enter weight of edge: ";
							double weight = Number();
							Edge<double> tmp(vertex1, vertex2, weight);
							if (!graph.removeEdge(tmp))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")_"
										  << weight << " doesn't exist";
							}
							else
							{
								std::cout << "Edge erased" << std::endl;
							}
							break;
						}
						case (6):
						{
							std::cout << "Enter first vertex: ";
							double vertex1 = Number();
							std::cout << "Enter second vertex: ";
							double vertex2 = Number();
							if (!graph.removeEdge(vertex1, vertex2))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")"
										  << " doesn't exist";
							}
							else
							{
								std::cout << "Edge erased" << std::endl;
							}
							break;
						}
						case (7):
						{
							std::cout << "Enter first vertex: ";
							double vertex1 = Number();
							std::cout << "Enter second vertex: ";
							double vertex2 = Number();
							std::vector<double> tmp = graph.shortestPath(vertex1, vertex2);
							if (tmp.empty())
							{
								std::cout << "Shortest path doesn't exist" << std::endl;
							}
							else
							{
								std::cout << std::endl << "Shortest path: ";
								for (auto i : tmp)
								{
									std::cout << i << " ";
								}
							}
							std::cout << std::endl;
							break;
						}
						case (8):
						{
							std::cout << "Enter vertex: ";
							double vertex = Number();
							if (!graph.hasVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " doesn't exist";
							}
							else
							{
								std::cout << "DFS: ";
								graph.walk(vertex, Print<double>);
							}
							std::cout << std::endl;
							break;
						}
						case (9):
						{
							std::cout << graph;
							break;
						}
						case (10):
						{
							std::cout << "Exit!" << std::endl;
							exitM= true;
							break;
						}
						default:
							std::cout << "Error, try again" << std::endl;
							break;
						}
					}
					break;
				}
				case (3):
				{
					int choiceM;
					bool exitM= false;
					Graph<std::string> graph;
					while (!exitM)
					{
						menu11();
						choiceM = checkMenu10();
						switch (choiceM)
						{
						case (1):
						{
							std::cout << "Enter vertex: ";
							std::string vertex = " ";
							std::cin >> vertex;
							if (!graph.addVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " already exist";
							}
							else
							{
								std::cout << "Vertex added" << std::endl;
							}
							std::cout << graph;
							break;
						}
						case (2):
						{
							std::cout << "Enter vertex: ";
							std::string vertex = " ";
							std::cin >> vertex;
							if (!graph.removeVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " doesn't exist";
							}
							else
							{
								std::cout << "Vertex erased" << std::endl;
							}
							break;
						}
						case (3):
						{
							std::cout << "Enter first vertex: ";
							std::string vertex1 = " ";
							std::cin >> vertex1;
							std::cout << "Enter second vertex: ";
							std::string vertex2 = " ";
							std::cin >> vertex2;
							std::cout << "Enter weight of edge: ";
							double weight = Number();
							if (!graph.addEdge(vertex1, vertex2, weight))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")_"
										  << weight << " already exist or doesn't exist vertex1: " << vertex1
										  << " or vertex2: " << vertex2 << std::endl;
							}
							else
							{
								std::cout << "Edge added" << std::endl;
							}
							break;
						}
						case (4):
						{
							std::cout << "Enter first vertex: ";
							std::string vertex1 = " ";
							std::cin >> vertex1;
							std::cout << "Enter second vertex: ";
							std::string vertex2 = " ";
							std::cin >> vertex2;
							if (!graph.hasEdge(vertex1, vertex2))
							{
								std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
							}
							else
							{
								std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
							}
							break;
						}
						case (5):
						{
							std::cout << "Enter first vertex: ";
							std::string vertex1 = " ";
							std::cin >> vertex1;
							std::cout << "Enter second vertex: ";
							std::string vertex2 = " ";
							std::cin >> vertex2;
							std::cout << "Enter weight of edge: ";
							double weight = Number();
							Edge<std::string> tmp(vertex1, vertex2, weight);
							if (!graph.removeEdge(tmp))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")_"
										  << weight << " doesn't exist";
							}
							else
							{
								std::cout << "Edge erased" << std::endl;
							}
							break;
						}
						case (6):
						{
							std::cout << "Enter first vertex: ";
							std::string vertex1 = " ";
							std::cin >> vertex1;
							std::cout << "Enter second vertex: ";
							std::string vertex2 = " ";
							std::cin >> vertex2;
							if (!graph.removeEdge(vertex1, vertex2))
							{
								std::cout << "Error: edge " << "(" << vertex1 << ", " << vertex2 << ")"
										  << " doesn't exist";
							}
							else
							{
								std::cout << "Edge erased" << std::endl;
							}
							break;
						}
						case (7):
						{
							std::cout << "Enter first vertex: ";
							std::string vertex1 = " ";
							std::cin >> vertex1;
							std::cout << "Enter second vertex: ";
							std::string vertex2 = " ";
							std::cin >> vertex2;
							std::vector<std::string> tmp = graph.shortestPath(vertex1, vertex2);
							if (tmp.empty())
							{
								std::cout << "Shortest path doesn't exist" << std::endl;
							}
							else
							{
								std::cout << std::endl << "Shortest path: ";
								for (const auto& i : tmp)
								{
									std::cout << i << " ";
								}
							}
							std::cout << std::endl;
							break;
						}
						case (8):
						{
							std::cout << "Enter vertex: ";
							std::string vertex = " ";
							std::cin >> vertex;
							if (!graph.hasVertex(vertex))
							{
								std::cout << "Error: vertex " << vertex << " doesn't exist";
							}
							else
							{
								std::cout << "DFS: ";
								graph.walk(vertex, Print<std::string>);
							}
							std::cout << std::endl;
							break;
						}
						case (9):
						{
							std::cout << graph;
							break;
						}
						case (10):
						{
							std::cout << "Error!" << std::endl;
							exitM= true;
							break;
						}
						default:
							std::cout << "Error, try again" << std::endl;
							break;
						}
					}
					break;
				}
				case (4):
				{
					std::cout << "Exit" << std::endl;
					exit1 = true;
					break;
				}
				default:
					std::cout << "Error, try again" << std::endl;
					break;
				}
			}
			break;
		}
		case (2):
		{
			Graph<int> a;
			a.addVertex(1);
			a.addVertex(2);
			a.addVertex(3);
			a.addVertex(4);

			a.addEdge(1, 2, 1);
			a.addEdge(2, 1, 1);
			a.addEdge(1, 3, 1);
			a.addEdge(3, 1, 1);
			a.addEdge(1, 4, 1);
			a.addEdge(4, 1, 1);
			a.addEdge(2, 3, 2);
			a.addEdge(3, 2, 2);
			a.addEdge(3, 4, 2);
			a.addEdge(4, 2, 2);
			a.addEdge(2, 4, 2);
			a.addEdge(4, 2, 2);
			std::cout << a << std::endl;
			std::cout << "Optimal point is: " << a.findOptimal() << std::endl;
			break;
		}
		case (3):
		{
			Graph<std::string> a;
			a.addVertex("first");
			a.addVertex("second");
			a.addVertex("third");
			a.addEdge("first", "second", 2);
			a.addEdge("second", "third", 13);
			a.addEdge("third", "first", 4);
			a.addEdge("first", "third", 2);
			a.addEdge("third", "second", 9);
			std::cout << a << std::endl;
			std::cout << "Modified walk function signature with function 'Print<typeData>' for vertex 'first':"
					  << std::endl;
			a.walk("first", Print<std::string>);
			std::cout << "\n\n";
			break;
		}
		case (4):
		{
			std::cout << "Exit!" << std::endl;
			exit = true;
			break;
		}
		default:
			std::cout << "Error, try again" << std::endl;
			break;
		}
	}
	return 0;
}