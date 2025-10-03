#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> manacher(const string& s, const function<bool(char, char)>& comp) {
    vector<int> radius(s.size());

    int c = 0, r = 0;
    for (int i = 0; i < s.size(); i += 2) {
        if (i <= r)
            radius[i] = min(r - i, radius[2 * c - i]);

        while (i - radius[i] - 1 >= 0 and i + radius[i] + 1 < s.size() and
               comp(s[i - radius[i] - 1], s[i + radius[i] + 1]))
            radius[i]++;

        if (i + radius[i] > r) {
            c = i;
            r = i + radius[i];
        }
    }

    return radius;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    string extended = "#";
    for (int i = 0; i < s.size(); i++) {
        extended.push_back(s[i]);
        extended.push_back('#');
    }

    vector<int> radius = manacher(extended, [](char a, char b) {
        if (a == '#' and b == '#')
            return true;
        return a != b;
    });

    long long ans = 0;
    for (int i = 0; i < extended.size(); i += 2)
        ans += radius[i] / 2;
    cout << ans;

    return 0;
}