#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int a[55], b[55], c[111];
bool isPossibleEnd[111][55][55];

constexpr int MAX_CART = 2'000'000;
bool isComposable[2'200'000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, s, n;
    cin >> r >> s >> n;

    for (int i = 1; i <= r; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= s; i++) {
        cin >> b[i];
        b[i] += b[i - 1];
    }
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    isComposable[0] = true;
    for (int i = 0; i <= MAX_CART; i++) {
        if (i - a[r] >= 0 and isComposable[i - a[r]])
            isComposable[i] = true;
        if (i - b[s] >= 0 and isComposable[i - b[s]])
            isComposable[i] = true;
    }

    isPossibleEnd[0][1][1] = true;
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= r; x++) {
            for (int y = 1; y <= s; y++) {
                if (not isPossibleEnd[i - 1][x][y])
                    continue;

                for (int j = 1; j <= r; j++) {
                    for (int k = 1; k <= s; k++) {
                        int sum = a[j - 1] - a[x - 1] + b[k - 1] - b[y - 1];
                        if (j < x)
                            sum += a[r];
                        if (k < y)
                            sum += b[s];

                        if (sum > c[i])
                            continue;

                        if (isComposable[c[i] - sum])
                            isPossibleEnd[i][j][k] = true;
                    }
                }
            }
        }
    }

    for (int x = 1; x <= r; x++) {
        for (int y = 1; y <= s; y++) {
            if (isPossibleEnd[n][x][y]) {
                println("Yes");
                return 0;
            }
        }
    }

    println("No");

    return 0;
}