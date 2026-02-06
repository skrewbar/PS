#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll T[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    T[0] = -1;
    for (int i = 1; i <= n; i++)
        cin >> T[i];

    stack<int> s;
    s.push(0);

    ll ans = 0;

    for (int i = 1; i <= n + 1; i++) {
        while (T[s.top()] >= T[i]) {
            ll t = T[s.top()];
            s.pop();

            ans = max(ans, (i - 1 - s.top()) * t);
        }
        s.push(i);
    }

    println("{}", ans);

    return 0;
}