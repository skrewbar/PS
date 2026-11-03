#include <bits/stdc++.h>
using namespace std;

int n, m;
char board[1010][1010];

bool transposed = false;
void transpose() {
    transposed = not transposed;

    for (int i = 1; i <= max(n, m); i++) {
        for (int j = 1; j <= i; j++) swap(board[i][j], board[j][i]);
    }

    swap(n, m);
}

constexpr string_view IP = "IP";
vector<int> cparity;
bool solveSamePairty() {
    int parity = -1;
    for (int i = 1; i <= n; i++) {
        if (cparity[i] == -1) continue;

        if (parity == -1) parity = cparity[i];
        else if (parity != cparity[i]) return false;
    }
    if (parity == -1) parity = 0;

    vector<int> iparity(m + 1, -1);
    for (int j = parity + 1; j <= m; j += 2) {
        for (int i = 1; i <= n; i++) {
            if (board[i][j] == '?') continue;

            int p = i % 2;
            if (board[i][j] == 'P') p ^= 1;

            if (iparity[j] == -1) iparity[j] = p;
            else if (iparity[j] != p) return false;
        }
    }
    for (int j = parity + 1; j <= m; j += 2)
        if (iparity[j] == -1) iparity[j] = 0;

    for (int j = 1; j <= m; j++) {
        if (j % 2 == parity) {
            for (int i = 1; i <= n; i++) board[i][j] = 'C';
            continue;
        }

        for (int i = 1; i <= n; i++) board[i][j] = IP[(i + iparity[j]) % 2];
    }

    return true;
}
bool solveDiffParity() {
    for (int parity = 0; parity < 2; parity++) {
        bool consistent = true;

        for (int i = 1, p = parity; i <= n; i++, p ^= 1) {
            for (int j = cparity[i] + 1; j <= m; j += 2) {
                if (board[i][j] == '?') continue;

                if (board[i][j] != IP[p]) {
                    consistent = false;
                    break;
                }
            }

            if (not consistent) break;
        }
        if (not consistent) continue;

        for (int i = 1, p = parity; i <= n; i++, p ^= 1) {
            for (int j = 1; j <= m; j++) {
                if (j % 2 == cparity[i]) board[i][j] = 'C';
                else board[i][j] = IP[p];
            }
        }

        return true;
    }

    return false;
}

bool solveRowAlter() {
    cparity.assign(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j] == '?') continue;

            if (board[i][j] == board[i][j - 1]) return false;

            int p = j % 2;
            if (board[i][j] != 'C') p ^= 1;

            if (cparity[i] == -1) cparity[i] = p;
            else if (cparity[i] != p) return false;
        }
    }

    if (solveSamePairty()) return true;

    for (int i = 1; i <= n; i++)
        if (cparity[i] == -1) cparity[i] = 0;
    if (solveDiffParity()) return true;

    return false;
}

void solve() {
    cin >> n >> m;
    transposed = false;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> board[i][j];
    }

    if (solveRowAlter() or (transpose(), solveRowAlter())) {
        if (transposed) transpose();

        cout << "yes\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) { cout << board[i][j]; }
            cout << '\n';
        }
    } else cout << "no\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
