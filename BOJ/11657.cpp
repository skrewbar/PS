#include <bits/stdc++.h>
using namespace std;

const int MAX = 500 * 10000;

struct Line {
    int from, to;
    int cost;
};


int main() {
    int n, m;
    cin >> n >> m;

    vector<int> dist(n+1, MAX);
    dist[1] = 0;
    vector<Line> lines(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        lines[i] = {a, b, c};
    }


    for (int i = 1; i <= n; i++) {
        for (Line line : lines) {
            int from = line.from, to = line.to;
            int cost = line.cost;
            if (dist[from] == MAX) continue;
            if (dist[from] + cost < dist[to]) {
                if (i == n) {
                    cout << -1;
                    return 0;
                }

                dist[to] = dist[from] + cost;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        cout << (dist[i] == MAX ? -1 : dist[i]) << "\n";
    }

    return 0;
}