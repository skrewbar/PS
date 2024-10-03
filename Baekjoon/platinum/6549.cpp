#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    while (n != 0) {
        ll ans = 0;

        vector<ll> height(n+2, 0);
        for (int i = 1 ; i <= n ; i++) {
            cin >> height[i];
        }

        stack<ll> s;
        s.push(0);
        for (int i = 1 ; i <= n + 1 ; i++) {
            while (not s.empty() and height[s.top()] > height[i]) {
                int temp = s.top();
                s.pop();
                ans = max(
                    ans,
                    height[temp] * (i - 1 - s.top())
                );
            }
            s.push(i);
        }
        cout << ans << '\n';


        cin >> n;
    }

    return 0;
}