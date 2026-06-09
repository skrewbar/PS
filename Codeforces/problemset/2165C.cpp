#include <bits/stdc++.h>
using namespace std;

int a[505050];

void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, greater<>());

    while (q--) {
        int c;
        cin >> c;

        int answer = 0;

        priority_queue<int> pq;
        pq.push(a[1]);
        int idx = 2;
        for (int i = 29; i >= 0; i--) {
            if (~c & (1 << i)) continue;

            if (pq.empty() and idx > n) {
                answer += c;
                break;
            }

            while (pq.empty() or pq.top() < a[idx])
                pq.push(a[idx++]);

            int top = pq.top();
            pq.pop();

            if (c <= top) break;
            if ((1 << i) <= top) {
                top -= 1 << i;
                c -= 1 << i;
                pq.push(top);
                continue;
            }

            answer += (1 << i) - top;
            c -= 1 << i;
        }

        cout << answer << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
