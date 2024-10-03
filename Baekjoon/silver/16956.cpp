#include <bits/stdc++.h>
using namespace std;


int main() {
    int r, c;
    cin >> r >> c;

    vector<string> pasture(r);
    for (int i = 0; i < r; i++) {
        cin >> pasture[i];
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (pasture[i][j] != 'W') continue;

            int delta[4] = {1, -1, 0, 0};
            for (int k = 0; k < 4; k++) {
                int ni = i + delta[k];
                int nj = j + delta[3-k];

                if (0 <= ni and ni < r and 0 <= nj and nj < c and pasture[ni][nj] == 'S') {
                    cout << 0;
                    return 0;
                }
            }
        }
    }

    cout << 1 << "\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (pasture[i][j] == '.') pasture[i][j] = 'D';
            cout << pasture[i][j];
        }
        cout << "\n";
    }
}