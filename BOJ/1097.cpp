#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct PatternMatcher {
    string pattern;
    vector<int> pi;

    PatternMatcher(const string& pattern)
        : pattern(pattern), pi(pattern.size()) {
        for (int i = 1, j = 0; i < (int)pattern.size(); i++) {
            while (j > 0 and pattern[i] != pattern[j])
                j = pi[j - 1];

            if (pattern[i] == pattern[j])
                pi[i] = ++j;
        }
    }

    int getMatchCount(const string& s) {
        int ret = 0;

        for (int i = 0, j = 0; i < (int)s.size(); i++) {
            while (j > 0 and s[i] != pattern[j])
                j = pi[j - 1];

            if (s[i] == pattern[j]) {
                j++;
                if (j == (int)pattern.size()) {
                    j = pi[j - 1];
                    ret++;
                }
            }
        }

        return ret;
    }
};

int n, k;
vector<string> words;

int getMagicStringCount(const string& s, int state) {
    if (state == (1 << n) - 1) {
        PatternMatcher pm(s);
        return (pm.getMatchCount(s + s) - 1 == k ? 1 : 0);
    }

    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (state & (1 << i)) continue;

        ret += getMagicStringCount(s + words[i], state | (1 << i));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    words = vector(n, string());
    for (int i = 0; i < n; i++)
        cin >> words[i];

    cin >> k;

    cout << getMagicStringCount("", 0);
}