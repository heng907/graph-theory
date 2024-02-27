#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
using namespace std;

#define INF LLONG_MAX

typedef pair<long long, long long> Edge;

struct Graph {
    int V;
    vector<vector<Edge>> adj;
    vector<long long> dist;

    Graph(int V) : V(V), adj(V), dist(V, INF) {}

    void addEdge(long long u, long long v, long long w) {
        adj[u].push_back(make_pair(v, w));
    }

    void shortestPath(int src) {
        priority_queue<Edge, vector<Edge>, std::greater<Edge>> pq;
        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto & edge : adj[u]) {
                int v = edge.first;
                long long weight = edge.second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }
};

int main() {
    int T, sub;
    cin >> T >> sub;

    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        Graph g_from_1(n + 5), g_from_n(n + 5), g_from_N(n + 5);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            g_from_1.addEdge(v, u, w); // Invert the edge set
            g_from_n.addEdge(v, u, w);
            g_from_N.addEdge(v, u, w);
        }

        // Calculating shortest paths
        g_from_1.shortestPath(1);
        g_from_n.shortestPath(n);

        for (int i = 1; i <= n; i++) {
            if (g_from_1.dist[i] < INF && g_from_n.dist[i] < INF) {
                g_from_N.addEdge(n + 1, i, g_from_1.dist[i] + g_from_n.dist[i]);
            }
        }

        g_from_N.shortestPath(n + 1);

        // Output results
        for (int i = 1; i <= n; i++) {
            long long distance = (k == 1) ? g_from_1.dist[i] : g_from_N.dist[i];
            if (distance >= INF) cout << "-1 ";
            else cout << distance << " ";
        }
        cout << endl;
    }
    return 0;
}
