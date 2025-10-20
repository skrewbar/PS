#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

bool canGo[55][55], completed[55], visited[55];
vector<int> adj[55];
bool isCycleExists(int now, int prev) {
    visited[now] = true;

    for (int next : adj[now]) {
        if (completed[next])
            continue;

        if (visited[next] or isCycleExists(next, now)) {
            completed[now] = true;
            return true;
        }
    }

    completed[now] = true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        string line;
        cin >> line;

        for (int j = 0; j < N; j++)
            canGo[i][j] = (line[j] == 'Y');
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (canGo[i][j] and not canGo[j][i])
                adj[i].push_back(j);
        }
    }

    for (int i = 0; i < N; i++) {
        if (completed[i])
            continue;

        if (isCycleExists(i, -1)) {
            cout << "NO";
            return 0;
        }

        fill(visited, visited + N, false);
    }

    cout << "YES";

    return 0;
}