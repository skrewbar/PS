#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int MOD = 1e9 + 7;

int height[101], cases[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, H;
    cin >> N >> H;

    for (int i = 0; i < N; i++)
        cin >> height[i];

    cases[0] = 1;
    for (int h = 1; h <= H; h++) {
        for (int i = 0; i < N; i++) {
            if (h - height[i] >= 0) {
                cases[h] += cases[h - height[i]];
                cases[h] %= MOD;
            }
        }
    }

    cout << cases[H];

    return 0;
}