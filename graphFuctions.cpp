#include "anime.hpp"
#include "utilities.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include <cstddef>
#include <ostream>
#include <string>
#include <iostream>
#include <set>
#include <vector>

enum option {BFS, DFS, EXIT};

void printEdges(UndirectedGraphWeight& graph) {
	// Impresion de nodos similares 
	std::set<std::string> names;
	//std::cout << "######## CREACION DE ARCOS ########" << std::endl;
	for (const auto& edge : graph.edges()) {
		/*
		std::cout << "Arco entre {" << edge.v1.name << "} y {" << edge.v2.name
		    << "} con peso de:  " << edge.weight << "\n";
		    */
		 names.insert(edge.v1.name);
	}

	//std::cout << std::endl;
	
	// Consulta de elementos adyacentes a un nodo
	/*
	std::cout << "######## PRUEBA DE ADYACENCIA ########" << std::endl;
	for (const auto& name : names) {
		std::cout << "Animes adyacentes a '" << name << "' son: ";
		for (const auto& adyacent : graph.neighbors(graph.find_vertex(name))) {
			std::cout << "{"<< adyacent.name << "} "; 
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/
	std::cout << "Cantidad de nodos con aristas disponibles: " << names.size() << std::endl << std::endl;
	return;
}

const Anime& selectStartNode(UndirectedGraphWeight& graph) {
	std::string name;
	std::cout << "Escribe el nombre del anime el cual sera como nodo inicial: ";
	std::getline(std::cin >> std::ws, name);
	return graph.find_vertex(name);
}

void printTrail(UndirectedGraphWeight& graph) {
	// Recorridos de grafos
	unsigned option = BFS;
	std::cout << "######## RECORRIDOS DE GRAFOS ########" << std::endl;
	 do {
		std::cout << "Selecciona el tipo de recorrido a realizar (0: BFS, 1: DFS, 2: Salir): ";
		std::cin >> option;
		switch (option) {
			case BFS:
				graph.print_bfs(selectStartNode(graph));
				std::cout << std::endl;
				break;
			case DFS:
				graph.print_dfs(selectStartNode(graph));
				std::cout << std::endl;
				break;
			case EXIT:
				std::cout << "Saliendo de recorridos de grafos..." << std::endl;
				break;
			default:
				std::cout << "Opcion invalida!" << std::endl;
				break;
		}
	 } while (option != EXIT);
	return;
}
 
void printPath(UndirectedGraphWeight& graph) {
	std::string name1, name2;
	std::vector<Anime> path;
	int option = BFS;
	std::cout << "####### ENCUENTRA CAMINOS ENTRE ANIMES ########" << std::endl;
	
	do {
		long double weight = 0.0;
		std::cout << "Seleccione las opciones (0: Camino BFS, 1: Camino DFS, 2: Salir): ";
		std::cin >> option;
		if (option == EXIT)
			break;
		std::cout << "Anime conocido: ";
		std::getline(std::cin >> std::ws, name1);
		std::cout << "Anime que desea encontrar si tiene relacion: ";
		std::getline(std::cin >> std::ws, name2);
		switch (option) {
			case BFS:
				path = graph.find_path_bfs(graph.find_vertex(name1), graph.find_vertex(name2));
				std::cout << "Camino BFS: " << std::endl;
				for (size_t i = 0; i < path.size(); i++) {
					std::cout << path[i].name << " ";
					if (i + 1 != path.size()) {  
						weight += graph.weight(path[i], path[i + 1]);
					}
				}
				std::cout << " --> Ponderacion: " << weight << std::endl;
				break;
			case DFS:
				path = graph.find_path_dfs(graph.find_vertex(name1), graph.find_vertex(name2));
				std::cout << "Camino DFS:" << std::endl;
				for (size_t i = 0; i < path.size(); i++) {
					std::cout << path[i].name << " ";
					if (i + 1 != path.size()) {  
						weight += graph.weight(path[i], path[i + 1]);
					}
				}
				std::cout << " --> Ponderacion: " << weight << std::endl;
				break;
			case EXIT:
				break;
			default:
				std::cout << "Opcion invalida!" << std::endl;
				weight = 0.0;
				break;
		}
	} while (option != EXIT);
}

int main() {
	UndirectedGraphWeight graph;
	long double threshold = 0.75;
	readCSV("anime.csv", graph); // Crea los nodos del grafo
	buildGraph(graph, threshold); // Crea los arcos dependiendo de la similitud de los nodos
	printEdges(graph);
	printTrail(graph);
	printPath(graph);
	
	
	return 1;
}
