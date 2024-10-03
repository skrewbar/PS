#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}


void bfs(int start, int end) {
    bool visited[10000];
    fill(visited, visited + 10000, false);
    queue<pair<int, string>> q;
    q.push({start, ""});
    visited[start] = true;

    while (not q.empty()) {
        pair<int, string> now = q.front();
        q.pop();

        if (now.first == end) {
            cout << now.second << '\n';
            return;
        }

        int D = 2 * now.first % 10000;
        int S = (now.first == 0) ? 9999 : now.first - 1;
        int L = now.first % 1000 * 10 + now.first / 1000;
        int R = now.first / 10 + now.first % 10 * 1000;

        if (not visited[D]) {
            q.push({D, now.second + "D"});
            visited[D] = true;
        }
        if (not visited[S]) {
            q.push({S, now.second + "S"});
            visited[S] = true;
        }
        if (not visited[L]) {
            q.push({L, now.second + "L"});
            visited[L] = true;
        }
        if (not visited[R]) {
            q.push({R, now.second + "R"});
            visited[R] = true;
        }
    }
}


int main() {
    fastio();

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        bfs(a, b);
    }

    return 0;
}