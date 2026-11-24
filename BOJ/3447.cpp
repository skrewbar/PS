#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s, '\n');
    while (not cin.eof()) {
        for (int i = 0 ; i < 100 ; i++) {
            s = regex_replace(s, regex("BUG"), "");
        }
        cout << s << '\n';
        getline(cin, s, '\n');
    }

    return 0;
}