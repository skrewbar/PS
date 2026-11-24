#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<tuple<int, int, int>> ans;

struct Tree {
    size_t size;
    vector<vector<int>> adj;

    Tree(size_t size) : size(size), adj(size) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

void liftup(const vector<vector<int>>& adj, int node, int parent) {
    ans.emplace_back(node, parent, 1);

    for (int child : adj[node]) {
        if (child == parent)
            continue;

        liftup(adj, child, node);
    }
}

void liftdown(const vector<vector<int>>& adj, int node, int parent) {
    for (int child : adj[node]) {
        if (child == parent)
            continue;

        liftdown(adj, child, node);
    }

    ans.emplace_back(node, 1, parent);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    Tree A(N + 1), B(N + 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        A.addEdge(u, v);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        B.addEdge(u, v);
    }

    for (int node : A.adj[1]) {
        for (int child : A.adj[node]) {
            if (child == 1)
                continue;

            liftup(A.adj, child, node);
        }
    }

    for (int node : B.adj[1]) {
        for (int child : B.adj[node]) {
            if (child == 1)
                continue;

            liftdown(B.adj, child, node);
        }
    }

    println("{}", ans.size());
    for (auto& [a, b, c] : ans)
        println("{} {} {}", a, b, c);

    return 0;
}