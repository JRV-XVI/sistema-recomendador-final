#include "undirectedGraphWeight.hpp"
#include <set>
#include <iterator>

// Función para calcular la similitud entre dos animes
long double calculateSimilarity(const Anime& a, const Anime& b) {
    // Similitud basada en géneros
    std::vector<std::string> commonGenres;
    std::set_intersection(a.genres.begin(), a.genres.end(), b.genres.begin(), b.genres.end(), std::back_inserter(commonGenres));
    long double genreSimilarity = static_cast<long double>(commonGenres.size()) / std::max(a.genres.size(), b.genres.size());

    // Similitud basada en tipo
    long double typeSimilarity = (a.type == b.type) ? 1.0 : 0.0;

    // Similitud basada en episodios (normalización)
    long double episodeDiff = std::abs(a.episodes - b.episodes);
    long double episodeSimilarity = 1.0 - (episodeDiff / std::max(a.episodes, b.episodes));

    // Similitud basada en rating
    long double ratingDiff = std::abs(a.rating - b.rating);
    long double ratingSimilarity = 1.0 - (ratingDiff / 10.0); // Normalizado entre 0 y 1

    // Similitud basada en miembros
    long double memberDiff = std::abs(a.members - b.members);
    long double memberSimilarity = 1.0 - (memberDiff / std::max(a.members, b.members));

    // Combinar las similitudes (puedes ajustar los pesos)
    long double similarity = (0.4 * genreSimilarity) +
                        (0.2 * typeSimilarity) +
                        (0.15 * episodeSimilarity) +
                        (0.15 * ratingSimilarity) +
                        (0.1 * memberSimilarity);

    return similarity;
}

void buildGraph(UndirectedGraphWeight& graph, long double threshold) {
    // Agregar arcos basados en similitud
    for (size_t i = 0; i < graph.vertices().size(); ++i) {
        for (size_t j = i + 1; j < graph.vertices().size(); ++j) {
            long double similarity = calculateSimilarity(graph.vertices()[i], graph.vertices()[j]);
            if (similarity >= threshold) {
                long double weight = 1.0 - similarity; // Ponderación inversa a la similitud
		if (weight > 0) {
		    graph.add_edge(graph.vertices()[i], graph.vertices()[j], weight);
		}
            }
        }
    }
    return;
}
