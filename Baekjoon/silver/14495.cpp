#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ll i, j, k;
    i = 0;
    j = k = 1;

    while (n--) {
        ll temp = i + k;
        swap(i, j);
        swap(j, k);
        k = temp;
    }

    cout << i << '\n';

    return 0;
}