#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> friends;
vector<bool> visited;


pair<int, int> min_early_adapter_cnt(int root) {
    int adapter = 1, not_adapter = 0; // first, second
    for (int f : friends[root]) {
        if (visited[f]) continue;
        visited[f] = true;
        pair<int, int> adapter_cnts = min_early_adapter_cnt(f);
        not_adapter += adapter_cnts.first;
        adapter += min(adapter_cnts.first, adapter_cnts.second);
    }
    return {adapter, not_adapter};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    friends.resize(n+1);
    visited.resize(n+1);

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        friends[u].push_back(v);
        friends[v].push_back(u);
    }

    visited[1] = true;
    auto [adapter, non_adapter] = min_early_adapter_cnt(1);
    cout << min(adapter, non_adapter);
}