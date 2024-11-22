#ifndef ANIME_HPP
#define ANIME_HPP

#include <string>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

class Anime {
public:
    int anime_id;
    string name;
    std::vector<std::string>  genres;
    string type;
    int episodes;
    float rating;
    int members;

    // Constructor por defecto
    Anime() = default;

    // Constructor con parámetros
    Anime(int id, const string& n, std::vector<std::string>& g, const string& t, int ep, float r, int m)
        : anime_id(id), name(n), genres(g), type(t), episodes(ep), rating(r), members(m) {}

    // Sobrecarga del operador < para ordenar alfabéticamente por nombre
    bool operator<(const Anime& other) const {
        return name < other.name;
    }

    bool operator==(const Anime& other) const {
        return name == other.name;
    }
    // Método para mostrar la información del anime
    void display() const {
        std::cout << "\nID: " << anime_id << "\nTítulo: " << name << "\nGénero(s): ";
        for (const auto& genre : genres) {
            std::cout << genre << " "; 
        }
        std::cout << "\nTipo: " << type
                << "\nEpisodios: " << episodes
                << "\nCalificación: " << rating
                << "\nMiembros: " << members
                << "\n------------------------------------\n";
    }

    struct Hash {
        std::size_t operator()(const Anime& anime) const {
            return std::hash<int>{}(anime.anime_id);
        }
    };

};

#endif // ANIME_HPP
