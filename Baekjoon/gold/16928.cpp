#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
using namespace std;

unordered_map<int, int> board;


int bfs() {
    int visited[101];
    fill(visited, visited+101, 0);

    queue<int> q;
    q.push(1);

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        if (now == 100) return visited[100];

        for (int next = now+1; next <= min(now+6, 100); next++) {
            int temp = (board.find(next) != board.end()) ? board[next] : next;
            if (visited[temp]) continue;

            visited[temp] = visited[now] + 1;
            q.push(temp);
        }
    }

    return 0; // <- 도달하지 않음
}


int main() { fastio
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n+m; i++) {
        int x, y;
        cin >> x >> y;
        board.insert({x, y});
    }

    cout << bfs();


    return 0;
}