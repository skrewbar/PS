#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;
using ll = long long;

vector<vector<int>> adj;
int N;
ll answer = 0;

ll findAnswer(int root = 1, int parent = 0) {
    ll ret = 1; // count of nodes of subtree

    for (int child : adj[root]) {
        if (child == parent)
            continue;

        ll childCnt = findAnswer(child, root);
        answer += childCnt * (childCnt - 1) / 2 + childCnt * (N - childCnt);
        ret += childCnt;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    adj.assign(N + 1, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findAnswer();
    cout << answer;
    return 0;
}