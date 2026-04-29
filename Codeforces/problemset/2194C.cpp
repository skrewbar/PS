#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

set<char> chars[50505];

int n, k;

string findPattern(int period) {
    string pattern;

    for (int i = 0; i < period; i++) {
        bool exists = false;

        for (char c : chars[i]) {
            bool possible = true;

            for (int j = i + period; j < n; j += period) {
                if (chars[j].find(c) == chars[j].end()) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                exists = true;
                pattern += c;
                break;
            }
        }

        if (not exists)
            return "";
    }
    
    return pattern;
}

void solve() {
    cin >> n >> k;

    vector<int> periods;
    for (int i = 1; i <= floor(sqrt(n)); i++) {
        if (n % i != 0)
            continue;
        periods.push_back(i);
        periods.push_back(n / i);
    }
    sort(all(periods));

    for (int i = 0; i < n; i++)
        chars[i].clear();

    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < n; j++)
            chars[j].insert(s[j]);
    }
    
    string pattern;
    for (int i = 0; i < n; i++)
        pattern += *chars[i].begin();

    for (int period : periods) {
        string s = findPattern(period);
        if (s.empty())
            continue;
        pattern = s;
        break;
    }
    
    int patternLen = pattern.length();
    for (int i = 0; i < n / patternLen; i++)
        cout << pattern;
    cout << '\n';
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