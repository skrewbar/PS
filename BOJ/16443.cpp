#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int maxSize = 101;
int grundy[maxSize][maxSize];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i < maxSize; i++) {
        for (int j = 1; j < maxSize; j++) {
            if (i == j)
                continue;

            vector<bool> isPossible(maxSize * 3);

            for (int k = 1; k < max(i, j); k++) {
                if (i - k > 0 and i - k != j)
                    isPossible[grundy[i - k][j]] = true;
                if (j - k > 0 and j - k != i)
                    isPossible[grundy[i][j - k]] = true;
                if (i - k > 0 and j - k > 0 and i - k != j - k)
                    isPossible[grundy[i - k][j - k]] = true;
            }

            while (isPossible[grundy[i][j]])
                grundy[i][j]++;
        }
    }

    int N;
    cin >> N;

    int g = 0;
    while (N--) {
        int l, c;
        cin >> l >> c;

        if (l == 0 or c == 0 or l == c) {
            cout << 'Y';
            return 0;
        }

        g ^= grundy[l][c];
    }

    cout << (g ? 'Y' : 'N');

    return 0;
}