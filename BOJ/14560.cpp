#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll A[30];

vector<ll> getDiffs(int l, int r) {
    vector<ll> diffs = {0};

    for (int p = l; p <= r; p++) {
        int n = diffs.size();
        vector<ll> temp;
        temp.reserve(n * 3);

        for (int i = 0, j = 0, k = 0; i < n or j < n or k < n;) {
            ll val = (i < n ? diffs[i] : LLONG_MAX);
            ll add = (j < n ? diffs[j] + A[p] : LLONG_MAX);
            ll sub = (k < n ? diffs[k] - A[p] : LLONG_MAX);

            ll minValue = min({val, add, sub});
            temp.push_back(minValue);

            if (val == minValue)
                i++;
            else if (add == minValue)
                j++;
            else
                k++;
        }

        swap(temp, diffs);
    }

    return diffs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
        cin >> A[i];

    ll D;
    cin >> D;

    vector<ll> left = getDiffs(0, N / 2), right = getDiffs(N / 2 + 1, N - 1);

    ll ans = 0;
    for (int i = 0, l = 0, r = 0; i < left.size(); i++) {
        while (l < right.size() and right[l] - left[i] < -D)
            l++;
        while (r < right.size() and right[r] - left[i] <= D)
            r++;
        ans += r - l;
    }

    cout << ans;

    return 0;
}