#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int score = 0;
    for (char c : s) {
        if (c == 'A') score |= 1;
        else if (c == 'G') score |= 1 << 1;
        else if (c == 'C') score |= 1 << 2;
        else score |= 1 << 3;
    }

    cout << score;

    return 0;
}