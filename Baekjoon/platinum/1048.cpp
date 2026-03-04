#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

string board[333];

ll cases[333][333], newCases[333][333];

vector<pair<int, int>> coords[26];
vector<pair<int, int>> adjCoords[333][333][26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, L;
    cin >> N >> M >> L;

    string word;
    cin >> word;

    for (int i = 1; i <= N; i++) {
        cin >> board[i];
        board[i] = "#" + board[i];

        for (int j = 1; j <= M; j++) {
            coords[board[i][j] - 'A'].emplace_back(i, j);

            if (board[i][j] == word[0])
                cases[i][j] = 1;
        }
    }

    for (int i = 1; i < word.size(); i++) {
        for (int r = 1; r <= N; r++) {
            for (int c = 1; c <= M; c++) {
                cases[r][c] +=
                    cases[r - 1][c] + cases[r][c - 1] - cases[r - 1][c - 1];
                cases[r][c] %= MOD;
            }
        }

        fill(&newCases[0][0], &newCases[N][M + 1], 0);

        auto getRangeSum = [&](int sRow, int sCol, int eRow, int eCol) -> ll {
            if (eRow < 1 or N < sRow)
                return 0;
            if (eCol < 1 or M < sCol)
                return 0;

            sRow = max(sRow, 1);
            sCol = max(sCol, 1);

            eRow = min(eRow, N);
            eCol = min(eCol, M);

            return cases[eRow][eCol] - cases[sRow - 1][eCol] -
                   cases[eRow][sCol - 1] + cases[sRow - 1][sCol - 1];
        };

        for (auto [row, col] : coords[word[i] - 'A']) {
            newCases[row][col] = cases[N][M];

            // square
            newCases[row][col] -=
                getRangeSum(row - 2, col - 2, row + 2, col + 2);
            newCases[row][col] %= MOD;

            // horizontal
            newCases[row][col] -= getRangeSum(row - 1, 1, row + 1, col - 3);
            newCases[row][col] %= MOD;

            newCases[row][col] -= getRangeSum(row - 1, col + 3, row + 1, M);
            newCases[row][col] %= MOD;

            // vertical
            newCases[row][col] -= getRangeSum(1, col - 1, row - 3, col + 1);
            newCases[row][col] %= MOD;

            newCases[row][col] -= getRangeSum(row + 3, col - 1, N, col + 1);
            newCases[row][col] %= MOD;
        }

        swap(cases, newCases);
    }

    ll answer = 0;
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= M; c++) {
            answer = (answer + cases[r][c]) % MOD;
        }
    }
    answer = (answer + MOD) % MOD;
    println("{}", answer);

    return 0;
}