#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
#include "dataStructures/trie.hpp"
#include "dataStructures/avl_tree.hpp"
#include "dataStructures/dynamicArray.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <chrono>

template <typename T>
void readCSV(const std::string& filename, T &dataStructure) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    
    unsigned lineNumber = 1; // Just for debuging
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Atributes variables
        std::string name, genres, type;
        int id = 0, episodes = -1, members = -1;
        float rating = -1.0f;
       
        // Control variables
        std::stringstream ss(line); // Use to read line
        std::string data; // Variable to store the information of CSV

        ++lineNumber; // Counts line in case of especial error in CSV
        //std::cout << "Line: " << lineNumber << std::endl;
       
        // Save ID
        std::getline(ss, data, ','); // Read the first line and saves it in data
        id = stoi(data);

        // Leer el campo "name" (manejar nombres con y sin comillas)
        std::getline(ss, name, ',');
        if (name[0] == '"') {
            while (name.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2); // Quitar comillas
        }

        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genres, ',');
        if (genres[0] == '"') {
            while (genres.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                genres += "," + temp;
            }
            genres = genres.substr(1, genres.size() - 2); // Quitar comillas
        }
        
        // Checa si existen generos
        if (genres == "")
            continue;
        
        // Separar los géneros en subcategorías y limpiarlos
        std::stringstream genreStream(genres);
        std::string genre;
        std::vector<std::string> vectorGenre;
        while (std::getline(genreStream, genre, ',')) {
            // Eliminar espacios al inicio y al final de cada género
            genre.erase(0, genre.find_first_not_of(" "));
            genre.erase(genre.find_last_not_of(" ") + 1);
            vectorGenre.push_back(genre);
        }
        
        // Save type
        getline(ss, data, ',');
        type = data;
        if (type == "")
            continue;

        // Save episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;
        if (episodes < 0) 
            continue;
        
        // Save rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;
        if (rating < 0)
            continue;

        // Save members
        getline(ss, data, ',');
        members = stoi(data);
        if (members < 200000)
            continue;
        
        // Create anime object
        Anime anime(id, name, vectorGenre, type, episodes, rating, members);
        
        if constexpr (std::is_same<T, std::vector<Anime>>::value) {
            dataStructure.push_back(anime); // Agregar al vector
        } else if constexpr (std::is_same<T, UndirectedGraphWeight>::value) {
            dataStructure.add_vertex(anime); // Create a node on graph
        }
    }
    file.close();
}

// Use vector to storage elements
template <typename T>
void extractUniques(const std::string& filename, T& uniqueGenre, T& uniqueTypes) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }


    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string data, name, genres, types;


        std::getline(ss, data, ',');
        // Leer el campo "name" (manejar nombres con y sin comillas)
        std::getline(ss, name, ',');
        if (name[0] == '"') {
            while (name.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2);  // Quitar comillas
        }
        
        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genres, ',');
        if (genres[0] == '"') {
            while (genres.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                genres += "," + temp;
            }
            genres = genres.substr(1, genres.size() - 2);  // Quitar comillas
        }

        // Separar los géneros en subcategorías y limpiarlos
        std::stringstream genreStream(genres);
        std::string genre;
        while (std::getline(genreStream, genre, ',')) {
            // Eliminar espacios al inicio y al final de cada género
            genre.erase(0, genre.find_first_not_of(" "));
            genre.erase(genre.find_last_not_of(" ") + 1);

            // Verificar si el género ya está en genresArray
            bool exists = false;
            for (int i = 0; i < uniqueGenre.size(); ++i) {
                if (uniqueGenre[i] == genre) {
                    exists = true;
                    break;
                }
            }

            // Agregar género si no existe en genresArray
            if (!exists) {
                uniqueGenre.push_back(genre);
            }
        }

        // Leer el campo "type" (manejar tipos con y sin comillas)
        std::getline(ss, types, ',');
        if (types[0] == '"') {
            while (types.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                types += "," + temp;
            }
            types = types.substr(1, types.size() - 2);  // Quitar comillas
        }

        // Separar los géneros en subcategorías y limpiarlos
        std::stringstream typeStream(types);
        std::string type;
        while (std::getline(typeStream, type, ',')) {
            // Eliminar espacios al inicio y al final de cada género
            type.erase(0, type.find_first_not_of(" "));
            type.erase(type.find_last_not_of(" ") + 1);

            // Verificar si el género ya está en uniqueTypes
            bool exists = false;
            for (int i = 0; i < uniqueTypes.size(); ++i) {
                if (uniqueTypes[i] == type) {
                    exists = true;
                    break;
                }
            }

            // Agregar género si no existe en uniqueTypes
            if (!exists) {
                uniqueTypes.push_back(type);
            }
        }
    }

    file.close();
    return;
}

// Time execution in nanoseconds
template<typename Func>
unsigned timeExecuation(Func func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

void construirTrie() {
    // Leer los datos del archivo CSV
    std::vector<Anime> animes;
    readCSV("anime.csv", animes);

    // Construir el Trie y medir el tiempo de construcción
    Trie trie;
    auto buildTime = timeExecuation([&]() {
        for (auto& anime : animes) {
            trie.insert(anime.name, &anime);
        }
    });
    std::cout << "Tiempo para construir el Trie: " << buildTime / 1e6 << " ms\n";

    // Realizar búsquedas
    std::string query;
    while (true) {
        std::cout << "\nIngrese el nombre del anime (parcial o completo, 'salir' para terminar): ";
        if (query.empty()) std::cin.ignore(); // Limpiar el buffer solo la primera vez
        std::getline(std::cin, query);

        if (query == "salir") {
            break;
        }

        // Imprimir el prefijo que se busca
        std::cout << "Buscando prefijo: " << query << "\n";

        // Medir el tiempo de búsqueda
        auto searchTime = timeExecuation([&]() {
            auto suggestions = trie.getSuggestions(query);
            if (suggestions.empty()) {
                std::cout << "No se encontraron coincidencias.\n";
                return;
            }

            // Mostrar las coincidencias
            std::cout << "Coincidencias encontradas:\n";
            for (size_t i = 0; i < suggestions.size(); ++i) {
                std::cout << i + 1 << ". " << suggestions[i].first << "\n";
            }

            // Selección del usuario
            int choice;
            std::cout << "Seleccione una opción (número) o 0 para cancelar: ";
            std::cin >> choice;
            std::cin.ignore(); // Limpiar el buffer

            if (choice > 0 && choice <= static_cast<int>(suggestions.size())) {
                Anime* selectedAnime = suggestions[choice - 1].second;
                selectedAnime->display();
            } else {
                std::cout << "Selección cancelada.\n";
            }
        });

        std::cout << "Tiempo de búsqueda: " << searchTime / 1e3 << " µs\n";
    }
}

void extractUniqueGenres(const std::string& filename, DynamicArray<std::string>& genresArray)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }


    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string data, name, genres;


        std::getline(ss, data, ',');

        // Leer el campo "name" (manejar nombres con y sin comillas)
        std::getline(ss, name, ',');
        if (name[0] == '"') {
            while (name.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2);  // Quitar comillas
        }

        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genres, ',');
        if (genres[0] == '"') {
            while (genres.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                genres += "," + temp;
            }
            genres = genres.substr(1, genres.size() - 2);  // Quitar comillas
        }

        // Separar los géneros en subcategorías y limpiarlos
        std::stringstream genreStream(genres);
        std::string genre;
        while (std::getline(genreStream, genre, ',')) {
            // Eliminar espacios al inicio y al final de cada género
            genre.erase(0, genre.find_first_not_of(" "));
            genre.erase(genre.find_last_not_of(" ") + 1);

            // Verificar si el género ya está en genresArray
            bool exists = false;
            for (int i = 0; i < genresArray.size(); ++i) {
                if (genresArray[i] == genre) {
                    exists = true;
                    break;
                }
            }

            // Agregar género si no existe en genresArray
            if (!exists) {
                genresArray.push_back(genre);
            }
        }
    }

    file.close();
}


void construirAVL() {
    // Extraer categorías únicas
    DynamicArray<std::string> uniqueCategories;
    extractUniqueGenres("anime.csv", uniqueCategories);

    // Crear el AVL Tree y cargar los animes
    AVLTree<std::string, std::vector<Anime*>> categoryAVL;
    std::vector<Anime> animes;
    readCSV("anime.csv", animes);

    // Construir el AVL y medir el tiempo
    auto buildTime = timeExecuation([&]() {
        for (const auto& category : uniqueCategories) {
            categoryAVL.insert(category, {});
        }
        for (auto& anime : animes) {
            for (const auto& genre : anime.genres) {
                categoryAVL[genre].push_back(&anime);
            }
        }
    });
    std::cout << "Tiempo para construir el AVL: " << buildTime / 1e6 << " ms\n";

    // Convertir el vector de objetos a un vector de punteros
    std::vector<Anime*> filteredResults;
    for (auto& anime : animes) {
        filteredResults.push_back(&anime);
    }

    // Inicializar las categorías disponibles
    DynamicArray<std::string> filteredCategories = uniqueCategories;

    std::vector<std::string> selectedCategories;
    while (!filteredCategories.empty()) {
        // Mostrar sólo categorías válidas
        std::cout << "\nSeleccione una categoría (teclea el número):\n";
        for (size_t i = 0; i < filteredCategories.size(); ++i) {
            std::cout << i + 1 << ". " << filteredCategories[i] << "\t";
            if ((i + 1) % 4 == 0) std::cout << "\n";
        }
        std::cout << "\nO teclea 0 para terminar.\nOpción: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;
        if (choice < 1 || choice > static_cast<int>(filteredCategories.size())) {
            std::cout << "Opción inválida.\n";
            continue;
        }

        const std::string& selectedCategory = filteredCategories[choice - 1];
        selectedCategories.push_back(selectedCategory);

        // Filtrar los resultados basados en la categoría seleccionada
        std::vector<Anime*> newResults;
        for (auto* anime : filteredResults) {
            if (std::find(anime->genres.begin(), anime->genres.end(), selectedCategory) != anime->genres.end()) {
                newResults.push_back(anime);
            }
        }
        filteredResults = std::move(newResults);

        // Eliminar la categoría seleccionada de las categorías disponibles
        filteredCategories.erase(choice - 1);

        // Actualizar las categorías filtradas basadas en los resultados actuales
        DynamicArray<std::string> newCategories;
        for (const auto* anime : filteredResults) {
            for (const auto& genre : anime->genres) {
                if (std::find(newCategories.begin(), newCategories.end(), genre) == newCategories.end() &&
                    std::find(selectedCategories.begin(), selectedCategories.end(), genre) == selectedCategories.end()) {
                    newCategories.push_back(genre);
                }
            }
        }
        filteredCategories = std::move(newCategories);
    }

    // Ordenar los resultados finales por calificación
    std::sort(filteredResults.begin(), filteredResults.end(), [](const Anime* a, const Anime* b) {
        return a->rating > b->rating;
    });

    // Preguntar al usuario cuántos resultados desea ver
    if (!filteredResults.empty()) {
        int numResults;
        do {
            std::cout << "¿Cuántos resultados desea ver? (Máximo " << filteredResults.size() << "): ";
            std::cin >> numResults;
            if (numResults < 1 || numResults > static_cast<int>(filteredResults.size())) {
                std::cout << "Número inválido. Intente de nuevo.\n";
            }
        } while (numResults < 1 || numResults > static_cast<int>(filteredResults.size()));

        // Mostrar los resultados
        std::cout << "\nAnimes encontrados:\n";
        for (int i = 0; i < numResults; ++i) {
            filteredResults[i]->display();
        }
    } else {
        std::cout << "No se encontraron animes.\n";
    }
}




#endif
