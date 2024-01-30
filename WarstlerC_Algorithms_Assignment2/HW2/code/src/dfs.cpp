#include <search.hpp>
#include <stack>

int dfs(Graph &G, int start, int destination, int numberOfBuilding, std::vector<int> &path) {
    // Please ignore the parameter of numberOfBuilding; this parameter is only used in BFS
    // Return the number of shortest path

    int N = G.n; // Number of nodes in the graph
    std::vector<bool> visited(N, false);
    std::vector<int> trace(N, -1);
    std::stack<int> stack;

    stack.push(start); // Push start to stack
    visited[start] = true;

    while (!stack.empty()) {
        int u = stack.top();        
        if (u == destination) {
            if(stack.size() + 1 < numberOfBuilding)
                break;
        }

        bool notVisitedYet = false; // prevents popping from stack when there are unvisited nodes
        int numberOfAdjacencyNodes = G.e[u].size();
        LinkedListNode<int> *p = G.e[u].getRoot();

        for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) {
            int v = p->value; // v is the adjacency node of u

            if (!visited[v]) {
                visited[v] = true;
                trace[v] = u; // Push v into stackA
                stack.push(v);
                notVisitedYet = true;
            }
        }

        if (!notVisitedYet) {
            stack.pop();
        }
    }

    int u = destination;
    while (u != -1) {
        path.insert(path.begin(), u);
        u = trace[u]; // Insert u into the front of path
    }

    return 0;
}
