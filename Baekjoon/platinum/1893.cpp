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

int find(const string& s, const string& pattern) {
    int n = s.size(), count = 0;

    vector<int> fail = getFail(pattern);
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 and s[i] != pattern[j])
            j = fail[j - 1];
        if (s[i] == pattern[j]) {
            j++;
            if (j == (int)pattern.size()) {
                count++;
                j = fail[j - 1];
            }
        }
    }

    return count;
}

void solve() {
    string a, w, s;
    cin >> a >> w >> s;

    map<char, char> next;
    for (int i = 0; i < (int)a.size(); i++)
        next[a[i]] = a[(i + 1) % a.size()];

    vector<int> shifts;
    for (int x = 0; x < (int)a.size(); x++) {
        if (find(s, w) == 1)
            shifts.push_back(x);

        for (int i = 0; i < (int)w.size(); i++)
            w[i] = next[w[i]];
    }

    switch (shifts.size()) {
        case 0:
            print("no solution\n");
            break;
        case 1:
            print("unique: {}\n", shifts.front());
            break;
        default:
            print("ambiguous: ");
            sort(shifts.begin(), shifts.end());
            for (int shift : shifts)
                print("{} ", shift);
            print("\n");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}