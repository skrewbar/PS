#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

struct Board {
    static constexpr int h = 6, w = 4;
    int score = 0;
    bool board[h][w] = {};

    void addBlock(const vector<int>& columns) {
        vector<pair<int, int>> blocks(columns.size());
        for (int i = 0; i < blocks.size(); i++)
            blocks[i] = {0, columns[i]};

        while (true) {
            bool canMoveDown = true;

            for (auto [r, c] : blocks) {
                if (r == h - 1 or board[r + 1][c]) {
                    canMoveDown = false;
                    break;
                }
            }

            if (not canMoveDown)
                break;

            for (auto& [r, c] : blocks)
                r++;
        }

        for (auto [r, c] : blocks)
            board[r][c] = true;

        scoring();

        int minRow = h;
        for (auto [r, _] : blocks)
            minRow = min(minRow, r);

        if (minRow >= 2)
            return;

        for (int i = 0; i < 2 - minRow; i++) {
            clear(h - 1);
            pullDown(h - 2);
        }
    }

    void scoring() {
        for (int r = h - 1; r >= 0; r--) {
            while (true) {
                bool all = true;

                for (int c = 0; c < w; c++)
                    if (not board[r][c])
                        all = false;

                if (not all)
                    break;
                score++;

                clear(r);
                pullDown(r - 1);
            }
        }
    }

    void clear(int row) { fill(board[row], board[row] + w, false); }

    void pullDown(int row) {
        for (int r = row; r >= 0; r--) {
            for (int c = 0; c < w; c++)
                swap(board[r][c], board[r + 1][c]);
        }
    }

    int count() {
        int ret = 0;

        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                if (board[r][c])
                    ret++;
            }
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Board green, blue;

    int N;
    cin >> N;

    while (N--) {
        int t, row, col;
        cin >> t >> row >> col;

        if (t == 1) {
            green.addBlock({col});
            blue.addBlock({row});
        } else if (t == 2) {
            green.addBlock({col, col + 1});
            blue.addBlock({row});
            blue.addBlock({row});
        } else if (t == 3) {
            green.addBlock({col});
            green.addBlock({col});
            blue.addBlock({row, row + 1});
        }
    }

    cout << green.score + blue.score << '\n' << green.count() + blue.count();

    return 0;
}