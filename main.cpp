#include "anime.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include "utilities.hpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <initializer_list>
#include <iostream>

void initialize_graph(UndirectedGraphWeight& graph) {
	readCSV("anime.csv", graph); // Initialize nodes
	unsigned time = timeExecuation([&]() {
		graph.find_vertex("Fate/Zero").display();
            });
	std::cout << "Time for searching Fate/Zero and display it in nanoseconds: " << time << std::endl;
	return;
}

int main() {
	UndirectedGraphWeight graph;
	std::vector<std::string> categories;
	extractUniqueCategories("anime.csv", categories);
	std::cout << "Number of categories: " << categories.size() << std::endl;
	initialize_graph(graph);
	/*
	readCSV("anime.csv", graph);
	graph.find_vertex("Fate/Zero").display();
	graph.find_vertex("Cowboy Bebop").display();
	graph.add_edge(graph.find_vertex("Fate/stay night Movie: Unlimited Blade Works"), graph.find_vertex("Fate/Zero"), 1);
	graph.add_edge(graph.find_vertex("Fate/stay night"), graph.find_vertex("Fate/stay night Movie: Unlimited Blade Works"), 1);
	graph.add_edge(graph.find_vertex("Overlord"), graph.find_vertex("Fate/stay night"), 1);
	graph.add_edge(graph.find_vertex("Overlord"), graph.find_vertex("Fate/Zero"), 1);
	graph.add_edge(graph.find_vertex("Cowboy Bebop"), graph.find_vertex("Fate/Zero"), 1);
	graph.add_edge(graph.find_vertex("Cowboy Bebop"), graph.find_vertex("Overlord"), 1);
	graph.print_dfs(graph.find_vertex("Fate/Zero"));
	*/
	return EXIT_SUCCESS;
}
