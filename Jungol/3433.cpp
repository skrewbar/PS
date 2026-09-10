#include <bits/stdc++.h>
using namespace std;

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

using ll = long long;

int A[101010], B[101010], height[101010], prefMax[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        cin >> A[i] >> B[i];

        if (A[i] == 0) continue;

        A[i] = N - A[i] + 1;
        B[i] = N - B[i] + 1;
    }

    ll ans = 0;

    for (int j = 1; j <= M; j++) {
        prefMax[j] = prefMax[j - 1];

        if (B[j] == 1) maximize(prefMax[j], A[j]);
    }

    int rMostH = 0;
    for (int j = M; j >= 1; j--) {
        if (B[j] == 1) maximize(rMostH, A[j]);
        int h = min(rMostH, prefMax[j]);

        height[j] = h;
        if (h == 0) continue;

        if (h < B[j] or B[j] == 0) ans += h;
        else if (B[j] <= h and h <= A[j]) ans += B[j] - 1;
        else ans += h - (A[j] - B[j] + 1);
    }

    fill(prefMax, prefMax + M + 5, 0);

    int l = 1;
    for (int j = 1; j <= M; j++) {
        if (B[j - 1] > 1 and B[j] <= A[j - 1] and
            B[j - 1] <= A[j]) {  // overlap
            prefMax[j] = prefMax[j - 1];
            maximize(prefMax[j], A[j]);
            continue;
        }
        // not overlap

        rMostH = 0;
        for (int k = j - 1; k >= l; k--) {
            maximize(rMostH, A[k]);
            int h = min(rMostH, prefMax[k]);

            int bottom = max(height[k], A[k]);

            ans += max(0, h - bottom);
        }

        if (B[j] > 1) {
            l = j;
            prefMax[j] = A[j];
        } else l = j + 1;
    }

    rMostH = 0;
    for (int k = M; k >= l; k--) {
        maximize(rMostH, A[k]);
        int h = min(rMostH, prefMax[k]);

        int bottom = max(height[k], A[k]);

        ans += max(0, h - bottom);
    }

    cout << ans;

    return 0;
}
