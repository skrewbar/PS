#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, h;
    cin >> n >> h;

    if (h < 2 * n - 1 or h > n * n or h == n * n - 2) {
        cout << "impossible";
        return 0;
    }

    vector<ll> tower;
    if (h == 2 * n + 1) {
        tower = {2 * n - 3, 3, 2 * n - 1};
        h = 0;
    } else {
        for (ll i = 2 * n - 1; 1 <= i and i <= h; i -= 2) {
            h -= i;
            tower.push_back(i);
        }
    }

    if (h == 2) {
        int c = tower.back();
        tower.pop_back();

        tower.push_back(c - 2);
        tower.push_back(3);
        tower.push_back(1);
    } else if (h) {
        if (h & 1) tower.push_back(h);
        else {
            tower.push_back(h - 1);
            tower.push_back(1);
        }
    }

    reverse(tower.begin(), tower.end());
    for (ll i : tower) cout << i << ' ';

    sort(tower.begin(), tower.end(), greater<>());
    tower.push_back(0);
    ll j = 2*n - 1;
    for (ll i : tower) {
        for (; j > i; j -= 2) cout << j << ' ';
        j = i - 2;
    }

    return 0;
}
