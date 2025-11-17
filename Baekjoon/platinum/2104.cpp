#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll A[101010], sum[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        sum[i] = sum[i - 1] + A[i];
    }

    stack<int> s;
    ll ans = 0;
    for (int i = 1; i <= N + 1; i++) {
        while (not s.empty() and A[s.top()] >= A[i]) {
            int m = A[s.top()];
            s.pop();

            int l = (s.empty() ? 0 : s.top());
            ans = max(ans, (sum[i - 1] - sum[l]) * m);
        }
        s.push(i);
    }

    cout << ans;

    return 0;
}