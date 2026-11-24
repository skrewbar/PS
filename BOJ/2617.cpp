#include <bits/stdc++.h>
using namespace std;

vector<int> heavy_adj[101];
vector<int> light_adj[101];
bool visited[101];


// 무거운 쪽으로 탐색
int get_heavier_cnt(int node) {
    int cnt = 0;
    for (int h : heavy_adj[node]) {
        if (visited[h]) continue;
        cnt += get_heavier_cnt(h) + 1;
        visited[h] = true;
    }
    return cnt;
}

// 가벼운 쪽으로 탐색
int get_lighter_cnt(int node) {
    int cnt = 0;
    for (int l : light_adj[node]) {
        if (visited[l]) continue;
        cnt += get_lighter_cnt(l) + 1;
        visited[l] = true;
    }
    return cnt;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while (m--) {
        int h, l;
        cin >> h >> l;
        heavy_adj[l].push_back(h);
        light_adj[h].push_back(l);
    }

    int mid = (n + 1) / 2;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        fill(visited, visited+101, false);
        int heavier_cnt = get_heavier_cnt(i);
        fill(visited, visited+101, false);
        int lighter_cnt = get_lighter_cnt(i);

        if (heavier_cnt >= mid or lighter_cnt >= mid) ans++;
        // cout << i << ' ' << heavier_cnt << ' ' << lighter_cnt << '\n';
    }
    
    cout << ans;
}