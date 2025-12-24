// graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graph.h"
int main()
{
	//std::cout << "hello";
	graph<char, int> g;
	g.add_vertex('A');
	g.add_vertex('B');
	g.add_vertex('C');
	g.add_vertex('D');

	g.add_edge('A', 'C', 2);
	g.add_edge('B', 'D', 3);
/*	g.add_edge('C', 'B', 5);
	g.add_edge('D', 'B', 6);
	g.add_edge('D', 'A', 1)*/;

	//std::cout << g.weight('A', 'C') << std::endl;
	//std::forward_list<char> neighbors;
	//neighbors = g.neighbors('D');
	//auto it = neighbors.begin();
	//std::cout << "Neighbors of D: ";
	//while (it != neighbors.end()) {
	//	std::cout << *it << " ";
	//	++it;
	//}

	//// check search dfs
	//if (g.search_dfs('A', 'B')) {
	//	std::cout << "path exists ";
	//}
	//else {
	//	std::cout << "path does not exists ";
	//}

	// check search dfs
	if (g.search_bfs('A', 'B')) {
		std::cout << "path exists ";
	}
	else {
		std::cout << "path does not exists ";
	}


}