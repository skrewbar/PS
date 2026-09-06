#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    vector<int> nums(3);
    cin >> nums[0] >> nums[1] >> nums[2];
    sort(all(nums));

    cout << min(nums[2] - nums[0], nums[1]) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
