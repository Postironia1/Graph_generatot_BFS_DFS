#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/**
 * A class representing a graph.
 */
class Graph {
public:
    /**
     * Constructor for the Graph class.
     *
     * @param vertices The number of vertices in the graph.
     * @param directed Whether the graph is directed (true) or undirected (false). Default is false.
     */
    Graph(int vertices, bool directed = false);

    /**
     * Adds an edge to the graph.
     *
     * @param u The starting vertex of the edge.
     * @param v The ending vertex of the edge.
     * @param weight The weight of the edge. Default is 1.
     */
    void add_edge(int u, int v, int weight = 1);

    /**
     * Returns the adjacency matrix of the graph.
     *
     * @return The adjacency matrix of the graph.
     */
    vector<vector<int>> get_adj_matrix();

    /**
    * Returns the adjacency list of the graph.
    *
    * @return The adjacency list of the graph.
    */
    vector<vector<pair<int, int>>> get_adj_list();

    /**
     * Returns the edges of the graph.
     *
     * @return The edges of the graph.
     */
    vector<pair<int, int>> get_edges();

    /**
     * Returns the incidence matrix of the graph.
     *
     * @return The incidence matrix of the graph.
     */
    vector<vector<int>> get_inc_matrix();

    /**
     * Prints the adjacency matrix of the graph.
     */
    void print_adj_matrix() const;

    /**
    * Prints the incidence matrix of the graph.
    */
    void print_inc_matrix() const;

    /**
     * Prints the adjacency list of the graph.
     */
    void print_adj_list() const;


private:
    int vertices_; // The number of vertices in the graph.
    bool directed_; // Whether the graph is directed or undirected.
    vector<vector<int>> adj_matrix_; // The adjacency matrix of the graph.
    vector<vector<pair<int, int>>> adj_list_; // The adjacency list of the graph.
    vector<pair<int, int>> edges_; // The edges of the graph.
    vector<vector<int>> inc_matrix_; // The incidence matrix of the graph.
};

/**
 * Constructor for the Graph class.
 * @param vertices The number of vertices in the graph.
 * @param directed A boolean indicating whether the graph is directed or undirected.
 */
Graph::Graph(int vertices, bool directed) {
    vertices_ = vertices;
    directed_ = directed;
    adj_matrix_ = vector<vector<int>>(vertices, vector<int>(vertices, 0));
    adj_list_ = vector<vector<pair<int, int>>>(vertices);
}

/**
 * Adds an edge between two vertices in the graph.
 * @param u The index of the first vertex.
 * @param v The index of the second vertex.
 * @param weight The weight of the edge.
 */
void Graph::add_edge(int u, int v, int weight) {
    adj_matrix_[u][v] = weight;
    adj_list_[u].push_back(make_pair(v, weight));
    edges_.push_back(make_pair(u, v));
    if (directed_) {
        adj_matrix_[u][v] = weight;
    }
    else {
        adj_matrix_[u][v] = adj_matrix_[v][u] = weight;
    }
}

/**
 * Returns the adjacency matrix of the graph.
 * @return A 2D vector representing the adjacency matrix.
 */
vector<vector<int>> Graph::get_adj_matrix() {
    return adj_matrix_;
}

/**
 * Returns the adjacency list of the graph.
 * @return A 2D vector representing the adjacency list.
 */
vector<vector<pair<int, int>>> Graph::get_adj_list() {
    return adj_list_;
}

/**
 * Returns the edges of the graph.
 * @return A vector of pairs representing the edges.
 */
vector<pair<int, int>> Graph::get_edges() {
    return edges_;
}

/**
 * Returns the incidence matrix of the graph.
 * @return A 2D vector representing the incidence matrix.
 */
vector<vector<int>> Graph::get_inc_matrix() {
    if (inc_matrix_.empty()) {
        inc_matrix_ = vector<vector<int>>(vertices_, vector<int>(edges_.size(), 0));
        for (int i = 0; i < edges_.size(); i++) {
            int u = edges_[i].first;
            int v = edges_[i].second;
            int weight = abs(adj_matrix_[u][v]);
            inc_matrix_[u][i] = weight;
            inc_matrix_[v][i] = directed_ ? -weight : weight;
        }
    }
    return inc_matrix_;
}

/**
 * Prints the adjacency matrix of the graph.
 */
void Graph::print_adj_matrix() const {
    cout << "  ";
    for (int i = 0; i < vertices_; i++) { cout << "V" << i << " "; }
    cout << endl;
    for (int i = 0; i < vertices_; i++) {
        cout << "V" << i << " ";
        for (int j = 0; j < vertices_; j++) {
            /*cout << adj_matrix_[i][j] << " ";*/
            if (adj_matrix_[i][j] > 0) cout << 1 << "  ";
            else cout << 0 << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Prints the incidence matrix of the graph.
 */
void Graph::print_inc_matrix() const {
    vector<vector<int>> inc_matrix(edges_.size(), vector<int>(vertices_, 0));
    int edge_idx = 0;
    for (int i = 0; i < vertices_; i++) {
        for (int j = i + 1; j < vertices_; j++) {
            if (adj_matrix_[i][j] != 0) {
                inc_matrix[edge_idx][i] = adj_matrix_[i][j];
                inc_matrix[edge_idx][j] = -adj_matrix_[i][j];
                edge_idx++;
            }
        }
    }
    cout << "  ";
    for (int i = 0; i < vertices_; i++) { cout << "V" << i << " "; }
    cout << endl;
    for (int i = 0; i < edges_.size(); i++) {
        cout << "E" << i << " ";
        for (int j = 0; j < vertices_; j++) {
            /*cout << inc_matrix[i][j] << " ";*/
            if (inc_matrix[i][j] != 0) cout << 1 << "  ";
            else cout << 0 << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Prints the adjacency list of the graph.
 */
void Graph::print_adj_list() const {
    for (int i = 0; i < vertices_; i++) {
        cout << i << ": ";
        for (int j = 0; j < vertices_; j++) {
            if (adj_matrix_[i][j] != 0) {
                cout << j << "(" << adj_matrix_[i][j] << ") ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Generates a random graph with the given parameters.
 *
 * @param min_vertices The minimum number of vertices in the graph.
 * @param max_vertices The maximum number of vertices in the graph.
 * @param min_edges The minimum number of edges in the graph.
 * @param max_edges The maximum number of edges in the graph.
 * @param max_edges_per_vertex The maximum number of edges per vertex.
 * @param directed Whether the graph is directed (true) or undirected (false).
 * @param max_incoming_edges The maximum number of incoming edges per vertex (if directed).
 * @param max_outgoing_edges The maximum number of outgoing edges per vertex (if directed).
 *
 * @return A randomly generated graph with the given parameters.
 */
Graph generate_graph(int min_vertices, int max_vertices, int min_edges, int max_edges, int max_edges_per_vertex, bool directed, int max_incoming_edges, int max_outgoing_edges) {
    srand(time(0));
    int num_vertices = rand() % (max_vertices - min_vertices + 1) + min_vertices;
    Graph g(num_vertices);
    int max_possible_edges = num_vertices * (num_vertices - 1) / 2;
    int max_possible_edges_per_vertex = num_vertices - 1;

    int num_edges = rand() % (max_edges - min_edges + 1) + min_edges;
    vector<int> edges_per_vertex(num_vertices, 0);
    vector<int> incoming_edges_per_vertex(num_vertices, 0);
    vector<int> outgoing_edges_per_vertex(num_vertices, 0);

    while (num_edges > 0) {
        int u = rand() % num_vertices;
        int v = rand() % num_vertices;
        if (u == v) {
            continue;
        }
        if (edges_per_vertex[u] >= max_possible_edges_per_vertex || edges_per_vertex[v] >= max_possible_edges_per_vertex) {
            continue;
        }

        if (directed && (incoming_edges_per_vertex[v] >= max_incoming_edges || outgoing_edges_per_vertex[u] >= max_outgoing_edges)) {
            continue;
        }

        if (g.get_adj_matrix()[u][v] != 0) {
            continue;
        }

        int weight = rand() % 100 + 1;
        g.add_edge(u, v, weight);
        num_edges--;
        edges_per_vertex[u]++;
        edges_per_vertex[v]++;

        if (directed) {
            incoming_edges_per_vertex[v]++;
            outgoing_edges_per_vertex[u]++;
        }

        if (num_edges == 0) {
            break;
        }
    }

    return g;
}

/**
 * Computes the shortest path between the given source and target vertices using BFS.
 *
 * @param g The graph to compute the shortest path on.
 * @param source The index of the source vertex.
 * @param target The index of the target vertex.
 *
 * @return A vector containing the indices of the vertices on the shortest path from source to target,
 * or an empty vector if there is no path between them.
 */
vector<int> bfs_shortest_path(Graph g, int source, int target) {
    int num_vertices = g.get_adj_matrix().size();
    vector<int> visited(num_vertices, 0);
    vector<int> parent(num_vertices, -1);
    queue<int> q;
    q.push(source);
    visited[source] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < num_vertices; v++) {
            if (g.get_adj_matrix()[u][v] != 0 && !visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (visited[target]) {
        vector<int> path;
        int u = target;
        while (u != -1) {
            path.push_back(u);
            u = parent[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
    else {
        return vector<int>();
    }
}

/**

This function performs depth-first search (DFS) starting from a given source vertex in a given graph,
and returns the shortest path from the source vertex to the target vertex, if one exists.
@param g: The input graph represented as an adjacency matrix.
@param source: The source vertex to start the DFS from.
@param target: The target vertex to find the shortest path to.
@return A vector of integers representing the vertices in the shortest path from the source to the target.
If no path exists, an empty vector is returned.
*/
vector<int> dfs_shortest_path(Graph g, int source, int target) {
    // Initialize the necessary data structures
    int num_vertices = g.get_adj_matrix().size();
    vector<int> visited(num_vertices, 0);
    vector<int> parent(num_vertices, -1);
    stack<int> s;
    s.push(source);
    visited[source] = 1;

    // Perform the DFS until the target vertex is found or the stack is empty
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (int v = 0; v < num_vertices; v++) {
            if (g.get_adj_matrix()[u][v] != 0 && !visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                s.push(v);
                if (v == target) {
                    break;
                }
            }
        }
    }

    // If the target vertex was found, construct the shortest path and return it
    if (visited[target]) {
        vector<int> path;
        int u = target;
        while (u != -1) {
            path.push_back(u);
            u = parent[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
    // Otherwise, return an empty vector to indicate that no path exists
    else {
        return vector<int>();
    }
}

int main() {
    srand(time(0));
    int min_vertices = 10;
    int max_vertices = 10;
    int min_edges = 10;
    int max_edges = 10;
    int max_edges_per_vertex = 10;
    int num_graphs = 10;
    int source = 0;
    int target = 0;


    for (int i = 0; i < num_graphs; i++) {

        int num_vertices = rand() % (max_vertices - min_vertices + 1) + min_vertices;
        int num_edges = rand() % (max_edges - min_edges + 1) + min_edges;
        Graph g = generate_graph(min_vertices, max_vertices, min_edges, max_edges, max_edges_per_vertex, false, 1, 1);
        source = rand() % num_vertices;
        target = rand() % num_vertices;



        cout << "Adjacency matrix:" << endl;
        g.print_adj_matrix();

        cout << "Incidence matrix:" << endl;
        g.print_inc_matrix();

        cout << "Adjacency list:" << endl;
        g.print_adj_list();

        cout << "Graph " << i + 1 << " with " << num_vertices << " vertices and " << num_edges << " edges" << endl;
        clock_t start_bfs = clock();
        vector<int> bfs_path = bfs_shortest_path(g, source, target);
        clock_t end_bfs = clock();
        double time_bfs = (double)(end_bfs - start_bfs) / CLOCKS_PER_SEC;
        cout << "BFS shortest path from vertex " << source << " to vertex " << target << ": ";
        if (!bfs_path.empty()) {
            for (int j = 0; j < bfs_path.size(); j++) {
                cout << bfs_path[j] << " ";
            }
            cout << endl;
        }
        else {
            cout << "Path does not exist" << endl;
        }
        cout << "BFS shortest path time: " << time_bfs << " seconds" << endl;

        clock_t start_dfs = clock();
        vector<int> dfs_path = dfs_shortest_path(g, source, target);
        clock_t end_dfs = clock();
        double time_dfs = (double)(end_dfs - start_dfs) / CLOCKS_PER_SEC;

        cout << "DFS shortest path from vertex " << source << " to vertex " << target << ": ";
        if (!dfs_path.empty()) {
            for (int j = 0; j < dfs_path.size(); j++) {
                cout << dfs_path[j] << " ";
            }
            cout << endl;
        }
        else {
            cout << "Path does not exist" << endl;
        }
        cout << "DFS shortest path time: " << time_dfs << " seconds ";
        cout << endl << endl << endl;

    }
    return EXIT_SUCCESS;
}