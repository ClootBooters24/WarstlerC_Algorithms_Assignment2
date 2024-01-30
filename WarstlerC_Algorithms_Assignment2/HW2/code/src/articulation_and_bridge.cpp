#include <graph.hpp>
#include <search.hpp>
/*
To iterate over the adjancy nodes of u, you can use the following template code 
int numberOfAdjacencyNodes = G.e[u].size(); // Get number of adjancy nodes of u 
LinkedListNode<int> *p = G.e[u].getRoot(); // Get the head point of the linked list
for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) { // iterate over each node
    int v = p->value; // v is the adjvancy node of u
    // YOUR CODE HERE
}


To create a pair of node u and v, you can use the following template
std::pair<int, int> bride(u, v);
 
*/

void findArticulationPointsAndBridges(Graph &G, std::vector<int> &articulationPoints, std::vector<std::pair<int, int> > &bridges) {
    int n = G.n; // Number of Nodes
    // YOUR CODE HERE
}
