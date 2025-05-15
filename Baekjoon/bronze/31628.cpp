#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> eggPlants(10, vector<string>(10));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cin >> eggPlants[i][j];
    }

    for (int i = 0; i < 10; i++) {
        bool row = true, column = true;
        for (int j = 1; j < 10; j++) {
            if (eggPlants[i][j] != eggPlants[i][j - 1])
                row = false;
            if (eggPlants[j][i] != eggPlants[j - 1][i])
                column = false;
        }
        if (row or column) {
            cout << 1;
            return 0;
        }
    }
    cout << 0;
}