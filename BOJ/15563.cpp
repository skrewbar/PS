#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N - 1; i++) {
        int ign;
        cin >> ign;
    }

    set<int> violin;
    while (Q--) {
        int type, u;
        cin >> type >> u;

        if (type == 1)
            violin.insert(u);
        else {
            if (violin.empty()) {
                cout << -1 << '\n';
                continue;
            }

            auto it = violin.upper_bound(u);
            int ans = N;
            if (it != violin.end() and *it - u < ans)
                ans = *it - u;
            if (it != violin.begin() and u - *--it < ans)
                ans = u - *it;

            cout << ans << '\n';
        }
    }

    return 0;
}