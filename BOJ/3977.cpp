#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> adj[101010];
int visitOrder[101010];
bool finished[101010];
int visitedCnt;
stack<int> s;
set<int> lastSCC;

int findSCC(int now) {
    s.push(now);
    int lowLink = visitOrder[now] = visitedCnt++;

    for (int nxt : adj[now]) {
        if (finished[nxt])
            continue;

        int nxtLowLink = visitOrder[nxt];
        if (nxtLowLink == -1)
            nxtLowLink = findSCC(nxt);

        lowLink = min(lowLink, nxtLowLink);
    }

    if (lowLink == visitOrder[now]) {
        lastSCC.clear();

        while (true) {
            int top = s.top();
            s.pop();

            finished[top] = true;
            lastSCC.insert(top);

            if (top == now)
                break;
        }
    }

    return lowLink;
}

void solve() {
    int N, M;
    cin >> N >> M;

    fill(adj, adj + N, vector<int>());
    while (M--) {
        int A, B;
        cin >> A >> B;

        adj[A].push_back(B);
    }

    fill(visitOrder, visitOrder + N, -1);
    fill(finished, finished + N, false);
    visitedCnt = 0;
    for (int i = 0; i < N; i++) {
        if (not finished[i])
            findSCC(i);
    }

    int start = *lastSCC.begin();
    vector<bool> visited(N);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (int nxt : adj[now]) {
            if (visited[nxt])
                continue;
            visited[nxt] = true;
            q.push(nxt);
        }
    }

    bool hasAnswer = true;
    for (int i = 0; i < N; i++) {
        if (not visited[i]) {
            hasAnswer = false;
            break;
        }
    }

    if (not hasAnswer) {
        cout << "Confused\n\n";
    } else {
        for (auto ans : lastSCC)
            cout << ans << '\n';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}