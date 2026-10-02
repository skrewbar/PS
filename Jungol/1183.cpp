#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int price[] = {500, 100, 50, 10, 5, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W;
    cin >> W;

    int total = 0;

    vector<int> cnt(6);
    for (int i = 0; i < 6; i++) {
        cin >> cnt[i];
        total += cnt[i] * price[i];
    }

    vector<int> ans(6);

    for (int i = 0; i < 6; i++) {
        int ex = total - cnt[i] * price[i];

        while (W - ex > 0) {
            W -= price[i];
            ans[i]++;
        }

        total -= cnt[i] * price[i];
    }

    cout << accumulate(all(ans), 0) << '\n';
    for (int i = 0; i < 6; i++) cout << ans[i] << ' ';

    return 0;
}
