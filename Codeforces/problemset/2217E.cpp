#include <bits/stdc++.h>
using namespace std;

array<int, 5050> arr;

int p[5050], d[5050], q[5050];

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> p[i];

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        if (d[i] == 0)
            pq.push(i);
    }

    int v = n;
    while (not pq.empty()) {
        int i = pq.top();
        pq.pop();

        q[i] = v--;
        for (int j = 1; j < i; j++) {
            if (p[j] > p[i])
                continue;

            if (--d[j] == 0)
                pq.push(j);
        }
    }
    if (v != 0) {
        println("-1");
        return;
    }

    for (int i = 1; i <= n; i++)
        print("{} ", q[i]);
    println();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}