#include <graph.hpp>

Graph::Graph(int n) {
    this->n = n;
    this->e = std::vector<LinkedList<int> >(n, LinkedList<int>());
}

Graph::~Graph() {
    this->e.clear();
}

void Graph::insertEdge(int u, int v, bool directed) {
    this->e[u].insert(v);
    if (not directed)
        this->e[v].insert(u);
}

int Graph::search(int start, int destination, int numberOfBuilding, int (*searchfn)(Graph &, int, int, int, std::vector<int>&), std::vector<int> &path) {
    path.clear();
    int count = searchfn(*this, start, destination, numberOfBuilding, path); 
    
    return count;
} 
