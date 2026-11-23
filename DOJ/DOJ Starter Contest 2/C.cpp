#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> cnt(4*N + 1);
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    for (int i = 1; i < 4*N; i++) {
        cnt[i + 1] += cnt[i] / 2;
    }

    for (int i = 4*N; i >= 1; i--) {
        if (cnt[i]) {
            cout << i;
            break;
        }
    }

    return 0;
}
