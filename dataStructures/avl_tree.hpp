#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>

// Nodo del árbol AVL
template <typename Key, typename Value>
class AVLNode {
public:
    Key key;
    Value value;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Key& k, const Value& v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

// Clase del árbol AVL
template <typename Key, typename Value>
class AVLTree {
private:
    AVLNode<Key, Value>* root;

    // Función auxiliar para obtener la altura de un nodo
    int getHeight(AVLNode<Key, Value>* node) const {
        return node ? node->height : 0;
    }

    // Rotación a la derecha
    AVLNode<Key, Value>* rotateRight(AVLNode<Key, Value>* y) {
        AVLNode<Key, Value>* x = y->left;
        AVLNode<Key, Value>* T = x->right;

        x->right = y;
        y->left = T;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Rotación a la izquierda
    AVLNode<Key, Value>* rotateLeft(AVLNode<Key, Value>* x) {
        AVLNode<Key, Value>* y = x->right;
        AVLNode<Key, Value>* T = y->left;

        y->left = x;
        x->right = T;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Obtener el factor de balance de un nodo
    int getBalance(AVLNode<Key, Value>* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Inserción en el árbol AVL
    AVLNode<Key, Value>* insert(AVLNode<Key, Value>* node, const Key& key, const Value& value) {
        if (!node) {
            return new AVLNode<Key, Value>(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value; // Actualizar valor si la clave ya existe
            return node;
        }

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        // Rotaciones para equilibrar el árbol
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Búsqueda en el árbol AVL
    AVLNode<Key, Value>* find(AVLNode<Key, Value>* node, const Key& key) const {
        if (!node || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return find(node->left, key);
        }
        return find(node->right, key);
    }

    // Eliminar el árbol
    void clear(AVLNode<Key, Value>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    // Insertar clave-valor en el árbol
    void insert(const Key& key, const Value& value) {
        root = insert(root, key, value);
    }

    // Verificar si existe una clave
    bool contains(const Key& key) const {
        return find(root, key) != nullptr;
    }

    // Obtener el valor asociado a una clave
    Value& operator[](const Key& key) {
        AVLNode<Key, Value>* node = find(root, key);
        if (!node) {
            insert(key, Value());
            node = find(root, key);
        }
        return node->value;
    }

    // Limpiar el árbol
    void clear() {
        clear(root);
        root = nullptr;
    }
};

#endif // AVL_TREE_HPP
