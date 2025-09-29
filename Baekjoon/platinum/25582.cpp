#include <bits/stdc++.h>
#include <algorithm>

#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

map<char, char> mirrorRule = {{'p', 'q'}, {'q', 'p'},

                              {'b', 'd'}, {'d', 'b'},

                              {'i', 'i'}, {'m', 'm'}, {'v', 'v'}, {'w', 'w'},

                              {'l', 'l'}, {'o', 'o'}, {'x', 'x'}, {'#', '#'}},

                pointRule = {{'p', 'd'}, {'d', 'p'},

                             {'b', 'q'}, {'q', 'b'},

                             {'u', 'n'}, {'n', 'u'}, {'s', 's'}, {'z', 'z'},

                             {'l', 'l'}, {'o', 'o'}, {'x', 'x'}, {'#', '#'}};

vector<int> manacher(const string& s, const map<char, char>& rule) {
    vector<int> a(s.size());
    int r = 0, c = 0;

    for (int i = 0; i < s.size(); i++) {
        if (r < i)
            a[i] = 0;
        else
            a[i] = min(r - i, a[2 * c - i]);

        auto it = rule.find(s[i]);
        if (it == rule.end() or it->second != s[i])
            continue;

        while ((i - a[i] - 1 >= 0) and (i + a[i] + 1 < s.size())) {
            it = rule.find(s[i - a[i] - 1]);
            if (it == rule.end() or it->second != s[i + a[i] + 1])
                break;

            a[i]++;
        }

        if (i + a[i] > r) {
            r = i + a[i];
            c = i;
        }
    }

    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string extended;
    extended.reserve(s.size() << 1);
    extended.push_back('#');
    for (char c : s) {
        extended.push_back(c);
        extended.push_back('#');
    }

    vector<int> mirrorA = manacher(extended, mirrorRule);
    int ans = *ranges::max_element(mirrorA);
    vector<int> pointA = manacher(extended, pointRule);
    ans = max(ans, *ranges::max_element(pointA));

    if (ans > 0)
        cout << ans;
    else
        cout << "NOANSWER";

    return 0;
}