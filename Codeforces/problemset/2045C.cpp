// 파이썬 쓰면 시간초과 나니 주의할 것.
#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;
    reverse(t.begin(), t.end());

    int prefix = s.size();
    int suffix = t.size();
    for (char a : "abcdefghijklmnopqrstuvwxyz") {
        int pre = 1;
        while (pre < s.size() and s[pre] != a) pre++;
        if (pre == s.size()) continue;

        int suf = 1;
        while (suf < t.size() and t[suf] != a) suf++;
        if (suf == t.size()) continue;

        if (pre + suf < prefix + suffix) {
            prefix = pre, suffix = suf;
        }
    }

    if (prefix == s.size() and suffix == t.size()) cout << -1;
    else {
        cout << s.substr(0, prefix+1);
        string suf = t.substr(0, suffix);
        reverse(suf.begin(), suf.end());
        cout << suf;
    }
}