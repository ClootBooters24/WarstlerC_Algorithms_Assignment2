#include <search.hpp>
#include <queue>

int bfs(Graph &G, int start, int destination, int numberOfBuilding, std::vector<int> &path) {
    // Please ignore the parameter of numberOfBuilding, this parameter is only used in DFS and Recursive DFS
    // Return the number of shortest path

    int N = G.n; // Number of nodes in the graph
    std::vector<bool> visited(N, false);
    std::vector<int> trace(N, -1);

    std::queue<int> queue;
    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        if (u == destination) {
            break;
        }

        int numberOfAdjacencyNodes = G.e[u].size();
        LinkedListNode<int> *p = G.e[u].getRoot();

        for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) {
            int v = p->value; // v is the adjacency node of u

            if (!visited[v]) {
                visited[v] = true;
                trace[v] = u;
                queue.push(v);
            }
        }
    }

    int u = destination;
    while (u != -1) {
        path.insert(path.begin(), u);
        u = trace[u];
    }

    return path.size();
}