#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

bool pattern[5][5] = {
    {false, false, true, false, false},
    {false, false, true, false, false},
    {true, true, true, true, true},
    {false, true, true, true, false},
    {false, true, false, true, false},
};


int pow(int base, int exp) {
    if (exp == 0) return 1;

    int x = pow(base, exp / 2);

    if (exp % 2 == 1) return x * x * base;
    else return x * x;
}


bool isStar(int x, int y, int i) {
    if (i == -1) return true;

    int nx = (x / pow(5, i)) % 5;
    int ny = (y / pow(5, i)) % 5;

    if (i == 0) return pattern[nx][ny];
    if (pattern[nx][ny]) return isStar(x, y, i-1);
    return false;
}


int main() {
    fastio();

    int n;
    cin >> n;

    for (int i = 0; i < pow(5, n); i++) {
        for (int j = 0; j < pow(5, n); j++) {
            if (isStar(i, j, n-1)) cout << '*';
            else cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}