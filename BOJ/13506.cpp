#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> getFail(const string& s) {
    vector<int> fail(s.size());

    for (int i = 1, j = 0; i < s.size(); i++) {
        while (j > 0 and s[i] != s[j])
            j = fail[j - 1];
        if (s[i] == s[j])
            fail[i] = ++j;
    }

    return fail;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    vector<int> fail = getFail(S);
    set<int> values;
    for (int i = 0; i < S.size() - 1; i++)
        values.insert(fail[i]);

    for (int i = fail.back(); i; i = fail[i - 1]) {
        if (values.contains(i)) {
            cout << S.substr(0, i);
            return 0;
        }
    }

    cout << -1;

    return 0;
}