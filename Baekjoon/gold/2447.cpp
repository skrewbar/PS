#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> answer;

/**
 * (i, j) 부터 (i+n, j+n)까지
 */
void makeStar(int i, int j, int n) {
    if (n == 1) {
        answer[i][j] = true;
        return;
    }

    int k = n / 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (r == 1 and c == 1) continue;
            makeStar(i + r*k, j + c*k, k);
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    answer.assign(n, vector<bool>(n, false));
    
    makeStar(0, 0, n);

    for (auto row : answer) {
        for (auto b : row) {
            cout << (b ? '*' : ' ');
        }
        cout << '\n';
    }
}