#include <bits/stdc++.h>
using namespace std;


int main() {
    string s;
    cin >> s;

    int diff = 0;
    for (char c : s) {
        diff += c == 'W' ? 1 : -1;
    }

    if (diff == 0) cout << 1;
    else cout << 0;
}