#include <bits/stdc++.h>
using namespace std;

class Board {
public:
    static vector<vector<char>> board;
    pair<int, int> red;
    pair<int, int> blue;

    Board() = default;
    Board(pair<int, int> red, pair<int, int> blue) : red(red), blue(blue) {}

    Board tilt(int dx, int dy) {
        auto red = this->red;
        auto blue = this->blue;

        while (board[red.first+=dx][red.second+=dy] == '.');
        while (board[blue.first+=dx][blue.second+=dy] == '.');

        if (board[blue.first][blue.second] == 'O') {
            board[0][0] = 'F';
            return Board(red, blue);
        }

        if (board[red.first][red.second] == 'O') {
            board[0][0] = 'S';
            return Board(red, blue);
        }

        board[0][0] = '#';
        red.first -= dx, red.second -= dy;
        blue.first -= dx, blue.second -= dy;

        if (red == blue) {
            if (abs(this->red.first - red.first) + abs(this->red.second - red.second) > abs(this->blue.first - blue.first) + abs(this->blue.second - blue.second)) {
                red.first -= dx, red.second -= dy;
            } else {
                blue.first -= dx, blue.second -= dy;
            }
        }
        return Board(red, blue);
    }

    Board tilt_up() {
        return tilt(-1, 0);
    }
    Board tilt_down() {
        return tilt(1, 0);
    }
    Board tilt_left() {
        return tilt(0, -1);
    }
    Board tilt_right() {
        return tilt(0, 1);
    }
};
vector<vector<char>> Board::board;


int get_min_count(Board board, int count = 0) {
    if (count > 10) return INT_MAX;

    if (count == 1) {
        int temp = 10;
        int ttemp = temp * temp;
    }

    if (board.board[0][0] == 'F') return INT_MAX;
    if (board.board[0][0] == 'S') return count;

    return min({
        get_min_count(board.tilt_up(), count+1),
        get_min_count(board.tilt_down(), count+1),
        get_min_count(board.tilt_left(), count+1),
        get_min_count(board.tilt_right(), count+1),
    });
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> &board = Board::board;
    board.resize(n);
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        Board::board[i] = vector<char>(row.begin(), row.end());
    }

    pair<int, int> red;
    pair<int, int> blue;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'R') {
                red = {i, j};
                board[i][j] = '.';
            } else if (board[i][j] == 'B') {
                blue = {i, j};
                board[i][j] = '.';
            }
        }
    }
    int ans = get_min_count(Board(red, blue));
    cout << (ans == INT_MAX ? -1 : ans);
}