#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> sudoku(9, vector<int>(9, 81));


void printSudoku() {
    for (int i = 0 ; i < 9 ; i++) {
        for (int j = 0 ; j < 9 ; j++) {
            cout << sudoku[i][j];
        }
        cout << '\n';
    }
}


bool available(int x, int y, int value) {
    for (int i = 0 ; i < 9 ; i++) {
        if (sudoku[i][y] == value or sudoku[x][i] == value) return false;
    }

    int bucketX = x / 3 * 3;
    int bucketY = y / 3 * 3;
    for (int i = bucketX ; i < bucketX+3 ; i++) {
        for (int j = bucketY ; j < bucketY+3 ; j++) {
            if (sudoku[i][j] == value) return false;
        }
    }
    return true;
}


bool dfs(int x, int y) {
    if (sudoku[x][y] != 0) { // 수를 채워야 하지 않으면 다음으로
        if (x == 8 and y == 8) return true;
        if (y < 8) return dfs(x, y+1);
        else return dfs(x+1, 0);
    }

    for (int value = 1 ; value <= 9 ; value++) {
        if (available(x, y, value)) {
            sudoku[x][y] = value;
            if (x == 8 and y == 8) return true;
            bool canFill = (y < 8) ? dfs(x, y+1) : dfs(x+1, 0);
            if (canFill) return true;
        }
    }
    sudoku[x][y] = 0;
    return false;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    for (int i = 0 ; i < 9 ; i++) {
        string str; cin >> str;
        for (int j = 0 ; j < 9 ; j++) {
            sudoku[i][j] = str[j] - '0';
        }
    }

    dfs(0, 0);
    printSudoku();


    return 0;
}