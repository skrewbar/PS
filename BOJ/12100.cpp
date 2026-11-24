#include <bits/stdc++.h>
using namespace std;

template <typename T>
using Matrix = vector<vector<T>>;

Matrix<int> up(Matrix<int> board) {
    int size = board.size();
    Matrix<bool> merged(size, vector<bool>(size));

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) continue;

            int row = i-1;
            while (row >= 0 and board[row][j] == 0) row--;
            if (row < 0 or board[row][j] != board[i][j] or merged[row][j]) {
                swap(board[row+1][j], board[i][j]);
            } else {
                board[row][j] <<= 1;
                board[i][j] = 0;
                merged[row][j] = true;
            }
        }
    }
    return board;
}

Matrix<int> down(Matrix<int> board) {
    int size = board.size();
    Matrix<bool> merged(size, vector<bool>(size));

    for (int i = size-2; i >= 0; i--) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) continue;

            int row = i+1;
            while (row < size and board[row][j] == 0) row++;
            if (row >= size or board[row][j] != board[i][j] or merged[row][j]) {
                swap(board[row-1][j], board[i][j]);
            } else {
                board[row][j] <<= 1;
                board[i][j] = 0;
                merged[row][j] = true;
            }
        }
    }
    return board;
}

Matrix<int> left(Matrix<int> board) {
    int size = board.size();
    Matrix<bool> merged(size, vector<bool>(size));

    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (board[i][j] == 0) continue;

            int column = j-1;
            while (column >= 0 and board[i][column] == 0) column--;
            if (column < 0 or board[i][column] != board[i][j] or merged[i][column]) {
                swap(board[i][column+1], board[i][j]);
            } else {
                board[i][column] <<= 1;
                board[i][j] = 0;
                merged[i][column] = true;
            }
        }
    }
    return board;
}

Matrix<int> right(Matrix<int> board) {
    int size = board.size();
    Matrix<bool> merged(size, vector<bool>(size));

    for (int i = 0; i < size; i++) {
        for (int j = size-2; j >= 0; j--) {
            if (board[i][j] == 0) continue;

            int column = j+1;
            while (column < size and board[i][column] == 0) column++;
            if (column >= size or board[i][column] != board[i][j] or merged[i][column]) {
                swap(board[i][column-1], board[i][j]);
            } else {
                board[i][column] <<= 1;
                board[i][j] = 0;
                merged[i][column] = true;
            }
        }
    }
    return board;
}


int max(const Matrix<int> &board) {
    int m = board[0][0];
    for (auto v : board) for (auto i : v) m = max(i, m);
    return m;
}

int max_number(Matrix<int> board, int count = 0) {
    if (count == 5) return max(board);
    count++;
    return max({
        max_number(up(board), count),
        max_number(down(board), count),
        max_number(left(board), count),
        max_number(right(board), count),
        });
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Matrix<int> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    cout << max_number(board);
}