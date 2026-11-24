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

int find(const string& target, const string& pattern) {
    vector<int> fail = getFail(pattern);
    int cnt = 0;

    for (int i = 0, j = 0; i < target.size(); i++) {
        while (j > 0 and target[i] != pattern[j])
            j = fail[j - 1];

        if (target[i] == pattern[j]) {
            if (j == pattern.size() - 1) {
                cnt++;
                j = fail[j];
            } else {
                j++;
            }
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    cin >> A >> B;

    B.append(B);
    B.pop_back();
    cout << find(B, A);

    return 0;
}