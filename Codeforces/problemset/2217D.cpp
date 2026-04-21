#include <bits/stdc++.h>
using namespace std;

int tempA[202020];
int a[202020];
bool isSpecial[202020];

int getBoundaryBetween(int l, int r) {
    int ret = 0;

    for (int i = l; i <= r; i++) {
        if (a[i] != a[i + 1])
            ret++;
    }

    return ret;
}

void solve() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<int> spIdx = {0};
    for (int i = 0; i < k; i++) {
        int idx;
        cin >> idx;
        spIdx.push_back(idx);
        isSpecial[idx] = true;
    }
    spIdx.push_back(n + 1);

    int x = a[spIdx[1]];
    a[0] = a[n + 1] = x;

    int maxBoundary = 0;
    int boundary = 0;
    
    for (int i = 0; i < k + 1; i++) {
        int b = getBoundaryBetween(spIdx[i], spIdx[i + 1] - 1);
        boundary += b;
        maxBoundary = max(maxBoundary, b);
    }

    println("{}", max(boundary / 2, maxBoundary));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}