#include <bits/stdc++.h>
using namespace std;


class DisjointSet {
private:
    vector<int> parent;
public:
    DisjointSet(int size) {
        parent.resize(size);
        for (int i = 0; i < size; i++) parent[i] = i;
    }

    int find_parent(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find_parent(parent[u]);
    }

    void union_parent(int u, int v) {
        parent[find_parent(u)] = find_parent(v);
    }
};


class Planet {
public:
    int x, y, z;

    Planet() = default;
    Planet(int x, int y, int z) : x(x), y(y), z(z) {}

    int cost(const Planet &p) {
        return min({abs(x - p.x), abs(y - p.y), abs(z - p.z)});
    }
};

class Edge {
public:
    int u, v, cost;

    Edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Planet> planet(n);
    vector<pair<int, int>> x_list(n), y_list(n), z_list(n);
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        planet[i] = Planet(x, y, z);
        x_list[i] = {x, i};
        y_list[i] = {y, i};
        z_list[i] = {z, i};
    }

    sort(x_list.begin(), x_list.end());
    sort(y_list.begin(), y_list.end());
    sort(z_list.begin(), z_list.end());

    vector<Edge> edges;
    edges.reserve(3*(n - 1));
    for (int i = 0; i < n-1; i++) {
        edges.push_back(Edge(x_list[i].second, x_list[i+1].second, x_list[i+1].first - x_list[i].first));
        edges.push_back(Edge(y_list[i].second, y_list[i+1].second, y_list[i+1].first - y_list[i].first));
        edges.push_back(Edge(z_list[i].second, z_list[i+1].second, z_list[i+1].first - z_list[i].first));
    }
    sort(edges.begin(), edges.end(), [](Edge &e1, Edge &e2) -> bool { return e1.cost < e2.cost; });

    DisjointSet set(n);
    long long ans = 0;
    int edge_count = 0;
    for (Edge edge : edges) {
        if (set.find_parent(edge.u) != set.find_parent(edge.v)) {
            set.union_parent(edge.u, edge.v);
            ans += edge.cost;
            edge_count++;
        }

        if (edge_count == n-1) break;
    }

    cout << ans;
}