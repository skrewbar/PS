#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int boardSize = 100;
int grundy[boardSize][boardSize];

void solve() {
    int N;
    cin >> N;

    int num = 0;
    bool alreadyWon = false;
    for (int i = 0; i < N; i++) {
        int X, Y;
        cin >> X >> Y;

        if (X == 0 or Y == 0 or X == Y)
            alreadyWon = true;

        num ^= grundy[X][Y];
    }

    if (alreadyWon)
        cout << "S\n";
    else
        cout << (num ? 'S' : 'D') << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            vector<bool> isPossible(boardSize * 3);
            if (i == j)
                continue;

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

    int T = 5;
    while (T--)
        solve();

    return 0;
}