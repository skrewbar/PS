#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> adj[202020];
bool isInCycle[202020];
int entryPoint[202020];

bool findCycle(int now, int prev, vector<bool>& visited) {
    static int startOfCycle = -1;

    visited[now] = true;

    for (int next : adj[now]) {
        if (next == prev)
            continue;

        if (visited[next]) {
            startOfCycle = next;
            return isInCycle[now] = true;
        }

        if (findCycle(next, now, visited)) {
            isInCycle[now] = true;

            return (now != startOfCycle);
        }
    }

    return false;
}

void findEntryPoint(int now, vector<bool>& visited) {
    visited[now] = true;

    for (int next : adj[now]) {
        if (visited[next] or isInCycle[next])
            continue;

        entryPoint[next] = entryPoint[now];
        findEntryPoint(next, visited);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visited(N + 1);
    findCycle(1, -1, visited);

    fill(visited.begin(), visited.end(), false);
    for (int i = 1; i <= N; i++) {
        if (isInCycle[i]) {
            entryPoint[i] = i;
            findEntryPoint(i, visited);
        }
    }

    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;

        if (entryPoint[u] != entryPoint[v])
            cout << 2 << '\n';
        else
            cout << 1 << '\n';
    }

    return 0;
}