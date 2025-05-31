#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getFailureFunction(const string& s) {
    int n = s.size();
    vector<int> fail(n);

    for (int i = 1, j = 0; i < n; i++) {
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

    string s;
    cin >> s;

    vector<int> fail = getFailureFunction(s);

    for (int i = 0; i < (int)s.size(); i++) {
        int repeatLen = i + 1 - fail[i];
        int repeatCount = (i + 1) / repeatLen;
        if (repeatCount > 1 and (i + 1) % repeatLen == 0)
            cout << format("{} {}\n", i+1, (i + 1) / repeatLen);
    }

    return 0;
}