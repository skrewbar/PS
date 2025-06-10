#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

int bucketSize;

struct Subarray {
    int l, r, order;

    bool operator<(const Subarray& s) {
        int bucket1 = l / bucketSize, bucket2 = s.l / bucketSize;
        if (bucket1 != bucket2)
            return bucket1 < bucket2;
        return r < s.r;
    }
};

array<int, 1'000'001> cnt = {};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    bucketSize = sqrt(n);
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<Subarray> subarrays(t);
    vector<ll> answer(t);
    for (int i = 0; i < t; i++) {
        auto& [l, r, order] = subarrays[i];
        order = i;
        cin >> l >> r;
        l--, r--;
    }
    sort(subarrays.begin(), subarrays.end());

    int l, r;
    l = r = subarrays[0].l;
    cnt[arr[l]]++;
    ll power = arr[l];

    for (Subarray subarray : subarrays) {
        while (l < subarray.l) {
            power -= ((cnt[arr[l]] << 1) - 1) * arr[l];
            cnt[arr[l]]--;
            l++;
        }
        while (l > subarray.l) {
            l--;
            power += ((cnt[arr[l]] << 1) + 1) * arr[l];
            cnt[arr[l]]++;
        }

        while (r < subarray.r) {
            r++;
            power += ((cnt[arr[r]] << 1) + 1) * arr[r];
            cnt[arr[r]]++;
        }
        while (r > subarray.r) {
            power -= ((cnt[arr[r]] << 1) - 1) * arr[r];
            cnt[arr[r]]--;
            r--;
        }

        answer[subarray.order] = power;
    }

    for (int i = 0; i < t; i++)
        cout << answer[i] << '\n';

    return 0;
}