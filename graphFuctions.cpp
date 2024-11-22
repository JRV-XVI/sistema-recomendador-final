#include "anime.hpp"
#include "utilities.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include <string>
#include <iostream>
#include <set>

void graphFunction() {
	UndirectedGraphWeight graph;
	long double threshold = 0.9989;
	readCSV("anime.csv", graph); // Crea los nodos del grafo
	buildGraph(graph, threshold); // Crea los arcos dependiendo de la similitud de los nodos
	
	// Impresion de nodos similares 
	std::set<std::string> names;
	std::cout << "######## CREACION DE ARCOS ########" << std::endl;
	for (const auto& edge : graph.edges()) {
		std::cout << "Arco entre '" << edge.v1.name << "' y '" << edge.v2.name
		    << "' con peso de:  " << edge.weight << "\n";
		 names.insert(edge.v1.name);
	}

	std::cout << std::endl;
	
	// Consulta de elementos adyacentes a un nodo
	std::cout << "######## PRUEBA DE ADYACENCIA ########" << std::endl;
	std::cout << "Cantidad de nodos con aristas disponibles: " << names.size() << std::endl << std::endl;
	for (const auto& name : names) {
		std::cout << "Animes adyacentes a '" << name << "' son: ";
		for (const auto& adyacent : graph.neighbors(graph.find_vertex(name))) {
			std::cout << "{"<< adyacent.name << "} "; 
		}
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
	
	// Recorridos de grafos
	std::cout << "######## RECORRIDOS DE GRAFOS ########" << std::endl;
}
 
int main() {
	
	graphFunction();
	return 1;
}
