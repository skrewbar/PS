#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> build_time(n+1);
    vector<vector<int>> next_nodes(n+1);
    vector<int> indegree(n+1);
    vector<int> pre_build_time(n+1);

    for (int i = 1; i <= n; i++) {
        cin >> build_time[i];

        int need;
        cin >> need;
        while (need != -1) {
            next_nodes[need].push_back(i);
            indegree[i]++;
            cin >> need;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (int next_node : next_nodes[now]) {
            indegree[next_node]--;
            pre_build_time[next_node] = max(pre_build_time[now] + build_time[now], pre_build_time[next_node]);

            if (indegree[next_node] == 0) {
                q.push(next_node);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << pre_build_time[i] + build_time[i] << '\n';
    }
}