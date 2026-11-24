#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int i, j;
    i = j = 1;

    while (n--) {
        i = (i + j + 1) % MOD;
        swap(i, j);
    }

    cout << i;

    return 0;
}