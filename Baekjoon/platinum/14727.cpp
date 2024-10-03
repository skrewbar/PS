#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll height[100002];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    fill(height, height+100002, 0);
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> height[i];
    }

    ll ans = 0;
    stack<ll> s;
    s.push(0);
    for (int i = 1 ; i <= n + 1 ; i++) {
        while (not s.empty() and height[s.top()] > height[i]) {
            ll temp = s.top();
            s.pop();
            ans = max(
                ans,
                height[temp] * (i - 1 - s.top())
            );
        }
        s.push(i);
    }

    cout << ans;


    return 0;
}