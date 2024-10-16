#include <bits/stdc++.h>
using namespace std;

using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n != 0) {
        vector<ll> height(n+1);
        for (int i = 0; i < n; i++) {
            cin >> height[i];
        }

        ll answer = 0;
        stack<int> s;
        for (int i = 0; i < n + 1; i++) {
            int pos = i;
            while (not s.empty() and height[s.top()] >= height[i]) {
                answer = max(height[s.top()] * (i - s.top()), answer);
                pos = s.top();
                s.pop();
            }
            height[pos] = height[i];
            s.push(pos);
        }

        cout << answer << "\n";

        cin >> n;
    }
}