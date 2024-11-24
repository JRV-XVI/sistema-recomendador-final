#include "anime.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include "utilities.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include "dataStructures/trie.hpp"


int main() {
    int choice = 0;

    do {
        std::cout << "\n--- Menú Principal ---\n";
        std::cout << "1. Optimización de búsquedas de productos (Trie)\n";
        std::cout << "2. Optimización de búsquedas de categorías (AVL)\n";
        std::cout << "3. Construcción de grafo de similitud\n";
        std::cout << "4. Recorrido en el grafo de similitudes\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                construirTrie();
                break;
            case 2:
                construirAVL();
                break;

            case 3:
                // Implementar la opción 3 aquí
                break;
            case 4:
                // Implementar la opción 4 aquí
                break;
            case 5:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, intente nuevamente.\n";
        }
    } while (choice != 5);

    return 0;
}