#include <bits/stdc++.h>
using namespace std;


int findArticulationEdges(
    int v, // vertex
    int parent,
    int &visitedCount,
    vector<vector<int>> &adj,
    vector<int> &visitOrder,
    vector<pair<int, int>> &articulationEdges
) {
    visitOrder[v] = visitedCount++;
    int lowLinkValue = visitOrder[v];
    for (int next : adj[v]) {
        if (next == parent) continue;
        if (visitOrder[next] != -1) {
            lowLinkValue = min(lowLinkValue, visitOrder[next]);
            continue;
        }

        int nextLowLinkValue = findArticulationEdges(next, v, visitedCount, adj, visitOrder, articulationEdges);
        if (nextLowLinkValue > visitOrder[v]) {
            articulationEdges.emplace_back(min(v, next), max(v, next));
        }
        lowLinkValue = min(lowLinkValue, nextLowLinkValue);
    }
    return lowLinkValue;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e;
    cin >> v >> e;
    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int visitedCount = 0;
    vector<int> visitOrder(v, -1);
    vector<pair<int, int>> articulationEdges;
    findArticulationEdges(0, 0, visitedCount, adj, visitOrder, articulationEdges);

    cout << articulationEdges.size() << '\n';
    sort(articulationEdges.begin(), articulationEdges.end());
    for (auto [a, b] : articulationEdges) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
}