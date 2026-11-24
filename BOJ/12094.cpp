#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int MOVE_LIMIT = 10;

int n, answer = 0;
int board[20][20];

void up() {
    queue<int> q;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++)
            if (board[i][j])
                q.push(board[i][j]), board[i][j] = 0;

        int i = 0;
        while (not q.empty()) {
            int elem = q.front();
            q.pop();
            if (board[i][j] == elem)
                board[i++][j] <<= 1;
            else if (board[i][j] == 0)
                board[i][j] = elem;
            else
                board[++i][j] = elem;
        }
    }
}

void down() {
    queue<int> q;
    for (int j = 0; j < n; j++) {
        for (int i = n - 1; i >= 0; i--)
            if (board[i][j])
                q.push(board[i][j]), board[i][j] = 0;

        int i = n - 1;
        while (not q.empty()) {
            int elem = q.front();
            q.pop();

            if (board[i][j] == elem)
                board[i--][j] <<= 1;
            else if (board[i][j] == 0)
                board[i][j] = elem;
            else
                board[--i][j] = elem;
        }
    }
}

void left() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (board[i][j])
                q.push(board[i][j]), board[i][j] = 0;

        int j = 0;
        while (not q.empty()) {
            int elem = q.front();
            q.pop();

            if (board[i][j] == elem)
                board[i][j++] <<= 1;
            else if (board[i][j] == 0)
                board[i][j] = elem;
            else
                board[i][++j] = elem;
        }
    }
}

void right() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--)
            if (board[i][j])
                q.push(board[i][j]), board[i][j] = 0;

        int j = n - 1;
        while (not q.empty()) {
            int elem = q.front();
            q.pop();

            if (board[i][j] == elem)
                board[i][j--] <<= 1;
            else if (board[i][j] == 0)
                board[i][j] = elem;
            else
                board[i][--j] = elem;
        }
    }
}

int getMaxOfBoard() {
    int m = board[0][0];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m = max(m, board[i][j]);
    
    return m;
}

void backTracking(int count = 0) {
    int m = getMaxOfBoard();
    answer = max(answer, m);

    if (count == MOVE_LIMIT) {
        return;
    }

    if ((m << (MOVE_LIMIT - count)) <= answer)
        return;

    int current[20][20];
    memcpy(current, board, sizeof(board));

    for (auto move : {up, down, left, right}) {
        move();

        bool different = false;
        for (int i = 0; i < n; i++) {
            if (different)
                break;
            for (int j = 0; j < n; j++)
                if (current[i][j] != board[i][j]) {
                    different = true;
                    break;
                }
        }

        if (different)
            backTracking(count + 1);

        memcpy(board, current, sizeof(current));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    backTracking();

    cout << answer;

    return 0;
}