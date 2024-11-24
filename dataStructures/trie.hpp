#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm> // Para transformar a minúsculas
#include "../anime.hpp"

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    Anime* anime; // Puntero al objeto Anime correspondiente

    TrieNode() : isEndOfWord(false), anime(nullptr) {}
};

class Trie {
private:
    TrieNode* root;

    // Función auxiliar para recopilar sugerencias recursivamente
    void collectSuggestions(TrieNode* node, const std::string& prefix, std::vector<std::pair<std::string, Anime*>>& suggestions) const {
        if (node->isEndOfWord) {
            suggestions.emplace_back(prefix, node->anime);
        }
        for (const auto& child : node->children) {
            collectSuggestions(child.second, prefix + child.first, suggestions);
        }
    }

public:
    Trie() : root(new TrieNode()) {}

    ~Trie() {
        clear(root);
    }

    void clear(TrieNode* node) {
        for (auto& child : node->children) {
            clear(child.second);
        }
        delete node;
    }

    // Insertar un nombre en el Trie
    void insert(const std::string& name, Anime* anime) {
        TrieNode* current = root;
        for (char c : name) {
            // Convertir a minúsculas para una búsqueda no sensible a mayúsculas
            c = std::tolower(c);
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
        current->anime = anime;
    }

    // Obtener sugerencias basadas en un prefijo
    std::vector<std::pair<std::string, Anime*>> getSuggestions(const std::string& prefix) const {
        TrieNode* current = root;
        std::string lowerPrefix;
        for (char c : prefix) {
            c = std::tolower(c);
            lowerPrefix += c;
            if (current->children.find(c) == current->children.end()) {
                return {}; // No se encontraron sugerencias
            }
            current = current->children[c];
        }
        std::vector<std::pair<std::string, Anime*>> suggestions;
        collectSuggestions(current, prefix, suggestions);
        return suggestions;
    }

    // Buscar un anime por nombre exacto
    Anime* search(const std::string& name) const {
        TrieNode* current = root;
        for (char c : name) {
            c = std::tolower(c);
            if (current->children.find(c) == current->children.end()) {
                return nullptr;
            }
            current = current->children[c];
        }
        if (current->isEndOfWord) {
            return current->anime;
        }
        return nullptr;
    }
};

#endif // TRIE_HPP
