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

    int n;
    string S;
    cin >> n >> S;

    vector<int> fail(n), minSuffPref(n);
    minSuffPref[0] = 1;
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 and S[i] != S[j])
            j = fail[j - 1];
        if (S[i] == S[j])
            fail[i] = ++j;

        minSuffPref[i] = fail[i] ? fail[i] : i + 1;
        if (minSuffPref[fail[i] - 1])
            minSuffPref[i] = minSuffPref[fail[i] - 1];
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans += i - minSuffPref[i] + 1;

    cout << ans;

    return 0;
}