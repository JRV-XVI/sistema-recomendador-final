#ifndef UNDIRECTED_GRAPH_WEIGHT_HPP
#define UNDIRECTED_GRAPH_WEIGHT_HPP

#include "../anime.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>

/**
 *  Structure that defines an edge in a graph.
 */
struct edge {

    Anime v1;          /**< The first vertex of the edge. */
    Anime v2;          /**< The second vertex of the edge. */
    long double weight;
};

/**
 *  Class that defines an undirected graph.
 * 
 *  The graph is represented as a collection of vertices and edges.
 */
class UndirectedGraphWeight {
public:

    /**
     *  Default constructor. 
     *
     *  It initializes the graph with an empty collection of vertices and edges.
     */
    UndirectedGraphWeight() = default;
    
    /**
     *  Clears the graph.
     */
    void clear()
    {
        vertices_.clear();
        edges_.clear();
        mapping_.clear();
    }

    /**
     *  Returns the vector with the vertices of the graph.
     * 
     *  @return A const reference to the vector with vertices of the graph.
     */
    const std::vector<Anime>& vertices() const 
    { 
        return vertices_; 
    }

    /**
     *  Returns the vector with the edges of the graph.
     *
     *  @return A const reference to the vector with edges of the graph.
     */
    const std::vector<edge>& edges() const
    {
        return edges_;
    }
    
    /**
     *  Returns weight of two vertices.
     *
     *  @return A const weight of two vertices.
     */
    const int weight(const Anime &v1, const Anime &v2) {
    // Check if the vertices exist
    for (const auto &ei : edges_) {
      if (ei.v1 == v1 && ei.v2 == v2)
        return ei.weight;
    }
    return -1;
  }

    /**
     *  Checks if the graph is empty.
     *
     *  @return True if the graph is empty, false otherwise.
     */
    bool empty() const
    {
        return vertices_.empty();
    }

    /**
     *  Adds a new vertex to the graph.
     *
     *  @param[in]  v   The identifier of the vertex.
     */
    void add_vertex(const Anime& v)
    {
        // Check if the vertex already exists
        if (contains_vertex(v)) {
            std::cout << "Vertex with the same id already exists" << std::endl;
            return;
        }        
        
        // Add the vertex to the collection of vertices.
        vertices_.push_back({ v });

        // Add the vertex to the mapping.
        mapping_[v] = vertices_.size() - 1;
    }

    /**
     *  Removes the specified vertex from the graph.
     *
     *  @param[in]  v   The identifier of the vertex to remove.
     * 
     *  @note This function uses the erase-remove idiom to remove the vertex from the collection of vertices.
     */
    void remove_vertex(const Anime& v)
    {
        // Check if the vertex exists
        if (mapping_.find(v) == mapping_.end()) {
            std::cout << "Vertex with the id does not exist" << std::endl;
            return;
        }

        // Remove the vertex from the mapping.
        mapping_.erase(v);

        // Remove the vertex from the collection of vertices.                
        auto new_vertices_end = std::remove(vertices_.begin(), vertices_.end(), v);
        vertices_.erase(new_vertices_end, vertices_.end());

        // Remove the edges that contain the vertex.
        auto new_edges_end = std::remove_if(edges_.begin(), edges_.end(),
            [&v](const edge& edge) {
                return edge.v1 == v || edge.v2 == v;
            });

        edges_.erase(new_edges_end, edges_.end());

    }

    /**
     *  Checks if the graph contains the specified vertex.
     *
     *  @param[in]  v   The identifier of the vertex to check.
     * 
     *  @return True if the graph contains the vertex, false otherwise.
     */
    bool contains_vertex(const Anime& v) const
    {
        return mapping_.find(v) != mapping_.end();
    }

    /**
     *  Adds a new edge to the graph.
     *
     *  @param[in]  v1  The identifier of the first vertex of the edge.
     *  @param[in]  v2  The identifier of the second vertex of the edge.
     */
    void add_edge(const Anime& v1, const Anime& v2, const long double weight)
    {
        // Check if the vertices exist
        if (!contains_vertex(v1) || !contains_vertex(v2)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return;
        }

        // Check if the edge is a loop
        if (v1 == v2) {
            std::cout << "The edge is a loop" << std::endl;
            return;
        }

        // Check if the edge already exists
        if (contains_edge(v1, v2)) {
            std::cout << "The edge already exist" << std::endl;
            return;
        }

        // Add the edge to the collection of edges.
        edges_.push_back({ v1, v2, weight });
    }

    /**
     *  Removes the specified edge from the graph.
     *
     *  @param[in]  v1  The identifier of the first vertex of the edge.
     *  @param[in]  v2  The identifier of the second vertex of the edge.
     */
    void remove_edge(const Anime& v1, const Anime& v2)
    {
        // Check if the edge exists
        if (!contains_edge(v1, v2)) {
            std::cout << "The edge does not exist" << std::endl;
            return;
        }

        // Remove the edge from the collection of edges.
        auto new_edges_end = std::remove_if(edges_.begin(), edges_.end(),
            [&v1, &v2](const edge& edge) {
                return (edge.v1 == v1 && edge.v2 == v2) || (edge.v1 == v2 && edge.v2 == v1);
            });

        edges_.erase(new_edges_end, edges_.end());
    }

    /**
     *  Checks if the graph contains the specified edge.
     *
     *  @param[in]  v1  The identifier of the first vertex of the edge
     *  @param[in]  v2  The identifier of the second vertex of the edge
     *
     *  @return True if the graph contains the edge, false otherwise.
     */
    bool contains_edge(const Anime& v1, const Anime& v2) const
    {
        for (const auto& ei : edges_) {
            if ((ei.v1 == v1 && ei.v2 == v2) || (ei.v1 == v2 && ei.v2 == v1))
                return true;
        }

        return false;
    }

    /**
     *  Returns the neighbors of the specified vertex.
     *
     *  @param[in]  v   The identifier of the vertex.
     *
     *  @return A vector with the identifiers of the neighbors of the vertex.
     */
    std::vector<Anime> neighbors(const Anime& v) const
    {   
        std::vector<Anime> result;

        for (const auto& e : edges_) {
            if (e.v1 == v)
                result.push_back(vertices_[mapping_.at(e.v2)]);
            else if (e.v2 == v)
                result.push_back(vertices_[mapping_.at(e.v1)]);
        }

        return result;
    }

    /**
     *  Returns the degree of the specified vertex.
     *
     *  @param[in]  v   The identifier of the vertex.
     *
     *  @return The degree of the vertex.
     */
    unsigned long long degree(const Anime& v) const
    {
        return neighbors(v).size();
    }

    /**
     *  Traverses the vertices of the graph starting from the specified vertex
     *  using a breadth-first search (BFS) algorithm.
     *
     *  @param[in]  start   The identifier of the vertex to start the traversal.
     *
     *  @return A vector with the identifiers of the vertices in BFS order.
     */
    std::vector<Anime> bfs(const Anime& start) const
    {
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return std::vector<Anime>();
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return std::vector<Anime>();
        }

        // Print the BFS traversal message
        std::cout << "BFS traversal from " << start.name << ": ";

        // Initialize the explored array and the frontier queue
        std::vector<bool> explored(vertices_.size(), false);
        std::queue<Anime> frontier;
        std::vector<Anime> visited;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the BFS traversal
        while (!frontier.empty()) {

            auto current = frontier.front();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            visited.push_back(vertices_[currentIndex]);

            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);
                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        return visited;
    }

    /**
     *  Traverses the vertices of the graph starting from the specified vertex
     *  using a breadth-first search (DFS) algorithm.
     *
     *  @param[in]  start   The identifier of the vertex to start the traversal.
     *
     *  @return A vector with the identifiers of the vertices in BFS order.
     */
    std::vector<Anime> dfs(const Anime& start) const
    {
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return std::vector<Anime>();
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return std::vector<Anime>();
        }

        // Print the DFS traversal message
        std::cout << "DFS traversal from " << start.name << ": ";

        // Initialize the explored array and the frontier stack
        std::vector<bool> explored(vertices_.size(), false);
        std::stack<Anime> frontier;
        std::vector<Anime> visited;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the DFS traversal
        while (!frontier.empty()) {

            Anime current = frontier.top();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            visited.push_back(vertices_[currentIndex]);

            for (const auto& neighborId : neighbors(current)) {

                auto it = mapping_.find(neighborId);

                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighborId);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        return visited;
    }

    /**
     *  Prints the vertices of the graph starting from the specified vertex 
     *  using a breadth-first search (BFS) traversal.
     *  
     *  @param[in]  start   The identifier of the vertex to start the traversal.
     */
    void print_bfs(const Anime& start) const
    {   
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return;
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return;
        }        

        // Print the BFS traversal message
        std::cout << "BFS traversal from " << start.name << ": ";

        // Initialize the explored array and the frontier queue
        std::vector<bool> explored(vertices_.size(), false);
        std::queue<Anime> frontier;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the BFS traversal
        while (!frontier.empty()) {

            auto current = frontier.front();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            std::cout << vertices_[currentIndex].name << " ";

            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);
                if (it != mapping_.end()) {
                    
                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        std::cout << std::endl;
    }

    /**
     *  Prints the vertices of the graph starting from the specified vertex
     *  using a breadth-first search (DFS) traversal.
     *
     *  @param[in]  start   The identifier of the vertex to start the traversal.
     */
    void print_dfs(const Anime& start) const
    {
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return;
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return;
        }    

        // Print the DFS traversal message
        std::cout << "DFS traversal from " << start.name << ": ";

        // Initialize the explored array and the frontier stack
        std::vector<bool> explored(vertices_.size(), false);
        std::stack<Anime> frontier;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the DFS traversal
        while (!frontier.empty()) {

            Anime current = frontier.top();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            std::cout << vertices_[currentIndex].name  << " ";

            for (const auto& neighborId : neighbors(current)) {

                auto it = mapping_.find(neighborId);
                
                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighborId);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        std::cout << std::endl;
    }

    /**
     *  Finds a path between two vertices using a breadth-first search (BFS) traversal.
     *
     *  @param[in]  start   The identifier of the start vertex.
     *  @param[in]  end     The identifier of the end vertex.
     *
     *  @return A vector with the identifiers of the vertices in the path.
     */
    std::vector<Anime> find_path_bfs(const Anime& start, const Anime& end) const
    {        
        std::vector<Anime> path;

        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return path;
        }

        // Check if the vertices exist
        if (!contains_vertex(start) || !contains_vertex(end)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return path;
        }

        // Initialize the explored array, the parents array, and the frontier queue        
        std::vector<bool> explored(vertices_.size(), false);
        std::unordered_map<Anime, Anime, Anime::Hash> parents;
        std::queue<Anime> frontier;

        // Add the start vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;
        parents[start] = Anime();

        // Perform the BFS traversal
        while (!frontier.empty()) {

            Anime current = frontier.front();
            frontier.pop();

            if (current == end) {
                //  The end vertex has been reached, reconstruct the path
                Anime pathVertex = current;
                
                while (pathVertex.name != "") {
                    path.push_back(pathVertex);
                    pathVertex = parents[pathVertex];
                }

                std::reverse(path.begin(), path.end());
                break;
            }

            // Explore the neighbors of the current vertex
            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);

                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second; 
                    
                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                        parents[neighbor] = current;
                    }

                }
            }
        }

        return path;
    }

    /**
     *  Finds a path between two vertices using a depth-first search (DFS) traversal.
     *
     *  @param[in]  start   The identifier of the start vertex.
     *  @param[in]  end     The identifier of the end vertex.
     *
     *  @return A vector with the identifiers of the vertices in the path.
     */
    std::vector<Anime> find_path_dfs(const Anime& start, const Anime& end) const
    {
        std::vector<Anime> path;

        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return path;
        }

        // Check if the vertices exist
        if (!contains_vertex(start) || !contains_vertex(end)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return path;
        }

        // Initialize the explored array, the parents array, and the frontier stack
        std::vector<bool> explored(vertices_.size(), false);
        std::unordered_map<Anime, Anime, Anime::Hash> parents;
        std::stack<Anime> frontier;

        // Add the start vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;
        parents[start] = Anime();

        // Perform the DFS traversal
        while (!frontier.empty()) {

            Anime current = frontier.top();
            frontier.pop();

            if (current == end) {
                //  The end vertex has been reached, reconstruct the path
                Anime pathVertex = current;

                while (pathVertex.name != "") {
                    path.push_back(pathVertex);
                    pathVertex = parents[pathVertex];
                }

                std::reverse(path.begin(), path.end());
                break;
            }

            // Explore the neighbors of the current vertex
            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);
                
                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                        parents[neighbor] = current;
                    }

                }
            }
        }

        return path;
    }
    
    Anime& find_vertex(const std::string& title) {
        for (Anime& anime : vertices_) {
            if (anime.name == title) {
                return anime;
            }
        }
        throw std::runtime_error("Anime not found");
    }

private:

    std::vector<Anime> vertices_;                             /**< The vertices of the graph. */

    std::vector<edge> edges_;                                       /**< The edges of the graph. */
    std::unordered_map<Anime, unsigned long long, Anime::Hash> mapping_;   /**< Mapping from vertex Ids to indices in `vertices_`. */
};

long double calculateSimilarity(const Anime& a, const Anime& b); 

void buildGraph(UndirectedGraphWeight& graph, long double treshold);

#endif
