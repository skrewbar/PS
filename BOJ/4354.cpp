#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getPi(const string& s) {
    vector<int> pi(s.size());
    for (int i = 1, j = 0; i < (int)s.size(); i++) {
        while (j > 0 and s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            pi[i] = ++j;
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    for (cin >> s; s != "."; cin >> s) {
        int patternLen = s.size() - getPi(s).back();
        cout << (s.size() % patternLen == 0 ? s.size() / patternLen : 1) << '\n';
    }
}