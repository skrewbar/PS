#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

#define value first
#define index second

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    deque<pair<int, int>> dq;
    for (int i = 1; i <= 2 * m - 2; i++) {
        int light;
        cin >> light;

        while (not dq.empty() and dq.back().value < light)
            dq.pop_back();
        dq.emplace_back(light, i);
    }

    for (int i = 2 * m - 1; i <= n; i++) {
        int light;
        cin >> light;

        while (not dq.empty() and dq.front().index < i - 2 * m + 2)
            dq.pop_front();

        while (not dq.empty() and dq.back().value < light)
            dq.pop_back();
        dq.emplace_back(light, i);

        print("{} ", dq.front().value);
    }

    return 0;
}