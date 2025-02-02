#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int vertices;
    vector<list<pair<int, int>>> adjList;

public:
    Graph(int V) : vertices(V) {
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    void dijkstra(int start) {
        vector<int> dist(vertices, 1e9);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, start});
        dist[start] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; ++i)
            cout << "Vertex " << i << ": " << (dist[i] == 1e9 ? "∞" : to_string(dist[i])) << "\n";
    }

    bool hasEulerianPath() {
        int oddDegreeCount = 0;
        for (const auto &neighbors : adjList) {
            if (neighbors.size() % 2 != 0)
                ++oddDegreeCount;
        }
        return oddDegreeCount == 0 || oddDegreeCount == 2;
    }

    void findEulerPath() {
        if (!hasEulerianPath()) {
            cout << "Eulerian path does not exist\n";
            return;
        }

        stack<int> stack;
        vector<int> path;
        vector<list<pair<int, int>>> tempAdjList = adjList;

        int start = 0;
        for (int i = 0; i < vertices; ++i) {
            if (tempAdjList[i].size() % 2 != 0) {
                start = i;
                break;
            }
        }

        stack.push(start);
        while (!stack.empty()) {
            int v = stack.top();
            if (!tempAdjList[v].empty()) {
                int u = tempAdjList[v].front().first;
                tempAdjList[v].pop_front();
                for (auto it = tempAdjList[u].begin(); it != tempAdjList[u].end(); ++it) {
                    if (it->first == v) {
                        tempAdjList[u].erase(it);
                        break;
                    }
                }
                stack.push(u);
            } else {
                path.push_back(v);
                stack.pop();
            }
        }

        cout << "Eulerian path: ";
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            cout << *it << " ";
        cout << endl;
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 5, 3);

    cout << "Dijkstra's Algorithm:\n";
    g.dijkstra(0);

    cout << "\nFinding Eulerian Path:\n";
    g.findEulerPath();

    return 0;
}
