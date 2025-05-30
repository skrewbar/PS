#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getFailureFunction(const string& s) {
    vector<int> fail(s.size());
    for (int i = 1, j = 0; i < (int)s.size(); i++) {
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

    int l;
    cin >> l;
    string s;
    cin >> s;

    cout << l - getFailureFunction(s).back();
}