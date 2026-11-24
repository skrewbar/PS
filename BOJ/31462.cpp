#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

enum Color : uint8_t { EMPTY, RED, BLUE } choco[5050][5050];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            char c;
            cin >> c;
            choco[i][j] = Color(c == 'R' ? RED : BLUE);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            if (choco[i][j] == RED) {
                if (choco[i + 1][j] != RED or choco[i + 1][j + 1] != RED) {
                    cout << 0;
                    return 0;
                }

                choco[i][j] = EMPTY;
                choco[i + 1][j] = EMPTY;
                choco[i + 1][j + 1] = EMPTY;
            } else if (choco[i][j] == BLUE) {
                if (choco[i][j + 1] != BLUE or choco[i + 1][j + 1] != BLUE) {
                    cout << 0;
                    return 0;
                }

                choco[i][j] = EMPTY;
                choco[i][j + 1] = EMPTY;
                choco[i + 1][j + 1] = EMPTY;
            }
        }
    }

    cout << 1;

    return 0;
}