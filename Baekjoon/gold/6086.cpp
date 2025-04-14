#include <bits/stdc++.h>
using namespace std;

int charToVertex(char c) {
    if ('A' <= c and c <= 'Z') return c - 'A';
    else return c - 'a' + 26;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> capacity(52, vector<int>(52));
    vector<vector<int>> flow(52, vector<int>(52));

    int n;
    cin >> n;
    while (n--) {
        char a, b;
        int c;
        cin >> a >> b >> c;

        int u = charToVertex(a), v = charToVertex(b);
        capacity[u][v] += c, capacity[v][u] += c;
    }

    int total_flow = 0;
    int source = charToVertex('A'),
        sink = charToVertex('Z');
    while (true) {
        queue<int> q;
        q.push(source);

        vector<int> parent(52, -1);
        parent[source] = source;
        while (not q.empty() and parent[sink] == -1) {
            int now = q.front();
            q.pop();

            for (int i = 0; i < 52; i++) {
                if (capacity[now][i] - flow[now][i] > 0 and parent[i] == -1) {
                    q.push(i);
                    parent[i] = now;
                }
            }
        }

        if (parent[sink] == -1) break;  // 증가 경로가 없는 경우

        int amount = 1e9;  // 증가 경로로 새로 흘려줄 유량 = 최소 잔여 용량
        for (int i = sink; i != source; i = parent[i]) {
            amount = min(capacity[parent[i]][i] - flow[parent[i]][i], amount);
        }

        for (int i = sink; i != source; i = parent[i]) {
            flow[parent[i]][i] += amount;
            flow[i][parent[i]] -= amount;
        }

        total_flow += amount;
    }

    cout << total_flow;
}