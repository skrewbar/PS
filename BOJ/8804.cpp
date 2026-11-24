#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());

        cout << 2 - (s == rev_s) << '\n';
    }
}