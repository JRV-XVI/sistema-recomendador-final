#include "anime.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include "utilities.hpp"
#include <set>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

int main() {
	std::vector<std::string> types, genres;
	extractUniques("anime.csv", genres, types);
	
	
	return EXIT_SUCCESS;
}
