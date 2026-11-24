#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getFail(const string& s) {
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

void solve(int tc, int n) {
    print("Test case #{}\n", tc);

    string s;
    cin >> s;

    vector<int> fail = getFail(s);
    for (int i = 1; i < n; i++) {
        int patternLen = (i + 1) - fail[i];
        int repeat = (i + 1) / patternLen;
        if ((i + 1) % patternLen == 0 and repeat > 1)
            print("{} {}\n", i + 1, (i + 1) / patternLen);
    }
    print("\n");

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int tc = 1; n != 0; tc++, cin >> n)
        solve(tc, n);

    return 0;
}