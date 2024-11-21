#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include "dataStructures/undirectedGraphWeight.hpp"
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
        std::string name, genre, type;
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
        std::getline(ss, genre, ',');
        if (genre[0] == '"') {
            while (genre.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                genre += "," + temp;
            }
            genre = genre.substr(1, genre.size() - 2); // Quitar comillas
        }
        
        if (genre == "")
            continue;

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
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);
        
        if constexpr (std::is_same<T, UndirectedGraphWeight>::value) {
            dataStructure.add_vertex(anime); // Create a node on graph
            continue;
        }
    }
    file.close();
}

// Use vector to storage elements
template <typename T>
void extractUniqueCategories(const std::string& filename, T& typesArray) {
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

            // Verificar si el género ya está en typesArray
            bool exists = false;
            for (int i = 0; i < typesArray.size(); ++i) {
                if (typesArray[i] == type) {
                    exists = true;
                    break;
                }
            }

            // Agregar género si no existe en typesArray
            if (!exists) {
                typesArray.push_back(type);
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

#endif
