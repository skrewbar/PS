#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int N, M, K;
int X, Y, Z;

vector<int> adj[101010];
pair<int, int> controlled;

int minTime[101010];
vector<int> prv[101010];

int dangerTime[101010];

void bfs(int start) {
    queue<int> q;
    q.push(start);

    fill(minTime + 1, minTime + N + 1, M + 1);
    fill(prv + 1, prv + N + 1, vector<int>());
    minTime[start] = 0;

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (int nxt : adj[cur]) {
            if (minTime[nxt] < minTime[cur] + 1) continue;
            prv[nxt].push_back(cur);
            if (minTime[nxt] == minTime[cur] + 1) continue;
            minTime[nxt] = minTime[cur] + 1;

            q.push(nxt);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    cin >> X >> Y >> Z;

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
        if (i == K) controlled = pair(a, b);
    }

    bfs(Y);
    fill(dangerTime + 1, dangerTime + N + 1, -1);

    queue<int> q;
    q.push(Z);
    vector<bool> visited(N + 1);
    visited[Z] = true;

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        dangerTime[cur] = minTime[cur];
        for (int p : prv[cur]) {
            if (visited[p]) continue;

            visited[p] = true;
            q.push(p);
        }
    }

    auto &vecf = adj[controlled.first];
    vecf.erase(find(vecf.begin(), vecf.end(), controlled.second));
    auto &vecs = adj[controlled.second];
    vecs.erase(find(vecs.begin(), vecs.end(), controlled.first));

    bool reachable = false;

    bfs(X);

    q.push(Z);
    visited.assign(N + 1, false);
    visited[Z] = true;

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == X) reachable = true;
        if (minTime[cur] == dangerTime[cur]) continue;

        for (int p : prv[cur]) {
            if (visited[p]) continue;

            visited[p] = true;
            q.push(p);
        }
    }

    if (minTime[Z] >= dangerTime[Z]) reachable = false;

    if (reachable) cout << "Burning Love";
    else cout << "GIVE ME CHOCO";

    return 0;
}
