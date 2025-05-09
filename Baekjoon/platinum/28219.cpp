#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> adj;
vector<bool> juyu;

int dfs(int root, int parent) {
    int firstMax = 0, secondMax = 0;

    for (int child : adj[root]) {
        if (child == parent)
            continue;

        int childHeight = dfs(child, root);
        if (childHeight > firstMax) {
            secondMax = firstMax;
            firstMax = childHeight;
        } else
            secondMax = max(secondMax, childHeight);
    }

    if (firstMax + secondMax >= k) {
        juyu[root] = true;
        return 0;
    }

    return firstMax + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    adj = vector(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    juyu = vector(n, false);
    dfs(0, -1);

    int answer = 0;
    for (int i = 0; i < n; i++)
        answer += juyu[i];
    cout << answer;
}