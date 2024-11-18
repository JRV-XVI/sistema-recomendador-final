#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <chrono>

template <typename T>
void readCSV(const std::string filename, T &dataStructure) 
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) 
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    
    unsigned lineNumber = 1; // Just for debuging
    std::getline(file, line);

    while (std::getline(file, line)) 
    {
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
        if (name[0] == '"') 
        {
            while (name.back() != '"') 
            {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2); // Quitar comillas
        }

        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genre, ',');
        if (genre[0] == '"') 
        {
            while (genre.back() != '"') 
            {
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
        if (episodes < 0) {
            continue;
        
        }
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

	/*
        while (true) 
        {
            if constexpr (std::is_same<T, DynamicArray<Anime>>::value) 
            {
                dataStructure.push_back(anime); // Is dynamic array
                break;
            } 
            else if constexpr (std::is_same<T, LinkedList<Anime>>::value) 
            {
                dataStructure.push_front(anime);
                break;
            }
            else if constexpr (std::is_same<T, DoublyLinkedList<Anime>>::value)
            {
                dataStructure.push_front(anime);
                break;
            }
            else if constexpr (std::is_same<T, PriorityQueue<Anime>>::value) 
            {
                dataStructure.push(anime, rating);
                break;
            }
        }
	*/
    }
    file.close();
}


#endif
