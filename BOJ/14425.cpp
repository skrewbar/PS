#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    set<string> s;
    while (n--) {
        string str;
        cin >> str;
        s.insert(str);
    }

    int ans = 0;
    while (m--) {
        string str;
        cin >> str;
        if (s.find(str) != s.end()) ans++;
    }
    cout << ans;
}