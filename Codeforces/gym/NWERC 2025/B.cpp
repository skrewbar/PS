#include <bits/stdc++.h>
using namespace std;

int prices[] = {1, 2, 5, 10, 20, 50, 100, 200, 500};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cnt(9);
    for (int i = 8; i >= 0; i--) {
        cnt[i] = n / prices[i];
        n %= prices[i];
    }

    auto printAns = [&]() {
        int sum = 0;
        for (int i = 0; i < 9; i++) sum += cnt[i];
        cout << sum << '\n';
        
        for (int i = 0; i < 9; i++) {
            while (cnt[i]--) cout << prices[i] << ' ';
        }
    };

    for (int i = 0; i < 9; i++) {
        if (cnt[i] % 2 == 1) {
            printAns();
            return 0;
        }
    }

    if (cnt[8] % 4 == 0) {
        cout << "splittable";
    } else {
        cnt[7] += cnt[8] * prices[8] / prices[7];
        cnt[8] = 0;
        printAns();
    }

    return 0;
}
