#ifndef ANIME_HPP
#define ANIME_HPP

#include <string>
#include <iostream>
#include <functional>

using namespace std;

class Anime {
public:
    int anime_id;
    string name;
    string genre;
    string type;
    int episodes;
    float rating;
    int members;

    // Constructor por defecto
    Anime() = default;

    // Constructor con parámetros
    Anime(int id, const string& n, const string& g, const string& t, int ep, float r, int m)
        : anime_id(id), name(n), genre(g), type(t), episodes(ep), rating(r), members(m) {}

    // Sobrecarga del operador < para ordenar alfabéticamente por nombre
    bool operator<(const Anime& other) const {
        return name < other.name;
    }

    bool operator==(const Anime& other) const {
        return name == other.name;
    }
    // Método para mostrar la información del anime
    void display() const {
        std::cout << "\nID: " << anime_id
                << "\nTítulo: " << name
                << "\nGénero(s): " << genre
                << "\nTipo: " << type
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
