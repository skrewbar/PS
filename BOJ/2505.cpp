#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> board(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> board[i];

    int lo = -1;
    for (int i = 1; i <= n; i++) {
        if (board[i] != i) {
            lo = i;
            break;
        }
    }
    if (lo == -1) {
        print("1 1\n1 1");
        return 0;
    }

    int hi = lo;
    while (board[hi] != lo)
        hi++;
    reverse(board.begin() + lo, board.begin() + hi + 1);

    int lo2 = -1;
    for (int i = 1; i <= n; i++) {
        if (board[i] != i) {
            lo2 = i;
            break;
        }
    }
    if (lo2 == -1) {
        print("{} {}\n1 1", lo, hi);
        return 0;
    }
    int hi2 = lo2;
    while (board[hi2] != lo2)
        hi2++;
    reverse(board.begin() + lo2, board.begin() + hi2 + 1);
    bool correct = true;
    for (int i = 1; i <= n; i++) {
        if (board[i] != i) {
            correct = false;
            break;
        }
    }
    if (correct) {
        print("{} {}\n{} {}", lo, hi, lo2, hi2);
        return 0;
    }

    reverse(board.begin() + lo2, board.begin() + hi2 + 1);
    reverse(board.begin() + lo, board.begin() + hi + 1);
    for (int i = n; i >= 1; i--) {
        if (board[i] != i) {
            hi = i;
            break;
        }
    }
    lo = hi;
    while (board[lo] != hi)
        lo--;
    reverse(board.begin() + lo, board.begin() + hi + 1);

    lo2 = -1;
    for (int i = 1; i <= n; i++) {
        if (board[i] != i) {
            lo2 = i;
            break;
        }
    }
    if (lo2 == -1) {
        print("{} {}\n1 1", lo, hi);
        return 0;
    }

    hi2 = lo2;
    while (board[hi2] != lo2)
        hi2++;

    print("{} {}\n{} {}", lo, hi, lo2, hi2);
}