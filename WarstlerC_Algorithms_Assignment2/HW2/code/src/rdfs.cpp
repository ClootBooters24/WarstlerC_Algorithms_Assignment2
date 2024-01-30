#include <search.hpp>
#include <vector>

int DFS(int u, Graph &G, std::vector<int> &path, std::vector<int> &visited, int destination, int numberOfBuilding) {
    path.push_back(u); // Push u into the path
    visited[u] = true;

    if (u == destination) {
  
        if(path.size() < numberOfBuilding + 1)
            return 1;
    }

    int numberOfAdjacencyNodes = G.e[u].size(); // Get number of adjancy nodes of u 
    LinkedListNode<int> *p = G.e[u].getRoot(); // Get the head point of the linked list
    for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) { // iterate over each node
         int v = p->value; // v is the adjvancy node of u
        
        // YOUR CODE HERE
        if (!visited[v]) {
            visited[v] = true;
            int flag = DFS(v, G, path, visited, destination, numberOfBuilding);
            if (flag == 1) {
                return 1;
            }
            visited[v] = false;
        }
    }

    path.pop_back(); // Remove u from the path
    return 0;
}

int rdfs(Graph &G, int start, int destination, int numberOfBuilding, std::vector<int> &path) {
    int N = G.n; // Number of nodes in the graph
    std::vector<int> visited(N, false);

    DFS(start, G, path, visited, destination, numberOfBuilding);

    return 0;
}