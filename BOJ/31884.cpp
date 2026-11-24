#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

map<int, ll> top;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    while (Q--) {
        int type, i;
        cin >> type >> i;

        if (type == 1) {
            ll y = 1;
            for (int x = i; x < i + 4; x++)
                y = max(y, (top.contains(x) ? top[x] : 0) + 1);

            for (int x = i; x < i + 4; x++)
                top[x] = y;
        } else if (type == 2) {
            ll y = (top.contains(i) ? top[i] : 0) + 4;
            top[i] = y;
        } else {
            println("{}", (top.contains(i) ? top[i] : 0));
        }
    }

    return 0;
}