#include "anime.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

int main() {
	UndirectedGraphWeight graph;
	long double threshold = 0.9987;
	std::vector<std::string> types, genres;
	extractUniques("anime.csv", genres, types);
	readCSV("anime.csv", graph);
	buildGraph(graph, threshold);
	for (const auto& edge : graph.edges()) {
	    std::cout << "Arco entre '" << edge.v1.name << "' y '" << edge.v2.name
                  << "' con peso de:  " << edge.weight << "\n";
	}
	
	return EXIT_SUCCESS;
}
