#include <iostream>
#include "Graph.cpp"

/* Функция проверки на целое */
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

/* Функция проверки числа от 1 до 4 */
int checkMenu()
{
	int number;
	while (!(std::cin >> number) || (std::cin.peek() != '\n') || number > 5 || number < 4)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect number, input again: ";
	}
	return number;
}

int main()
{
	Graph<std::string> a;
	a.addVertex("1");
	a.addVertex("2");
	a.addVertex("3");
	a.addVertex("4");
	a.addEdge("1", "2", 2);
	a.addEdge("1", "3", 2);
	a.addEdge("1", "4", 1);
	a.addEdge("4", "3", 1);
	a.shortestPath("1", "2");
	std::cout << a;
	a.walk("1", Print<std::string>);
	return 0;
}