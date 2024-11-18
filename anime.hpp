#ifndef ANIME_HPP
#define ANIME_HPP

#include <string>
#include <iostream>

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
    Anime() : anime_id(0), name(""), genre(""), type(""), episodes(0), rating(0.0), members(0) {}

    // Constructor con parámetros
    Anime(int id, const string& n, const string& g, const string& t, int ep, float r, int m)
        : anime_id(id), name(n), genre(g), type(t), episodes(ep), rating(r), members(m) {}

    // Sobrecarga del operador < para ordenar alfabéticamente por nombre
    bool operator<(const Anime& other) const {
        return name < other.name;
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

};

#endif // ANIME_HPP
