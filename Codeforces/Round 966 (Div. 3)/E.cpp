#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using MaxHeap = priority_queue<ll, vector<ll>, less<ll>>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m, k, w;
        cin >> n >> m >> k >> w;

        MaxHeap heights;
        MaxHeap counts;
        for (int i = 0; i < w; i++) {
            int height;
            cin >> height;
            heights.push(height);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                ll icount = min({i, n-i+1, k, n-k+1});
                ll jcount = min({j, m-j+1, k, m-k+1});
                counts.push(icount * jcount);
            }
        }

        ll answer = 0;
        while (not heights.empty()) {
            // cout << heights.top() << " " << counts.top() << "\n";
            answer += heights.top() * counts.top();
            heights.pop();
            counts.pop();
        }

        cout << answer << "\n";
    }

    return 0;
}