#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getZ(const string& s) {
    vector<int> z(s.size());
    z[0] = s.size();

    int l, r;
    l = r = 0;

    for (int i = 1; i < (int)s.size(); i++) {
        if (i <= r)
            z[i] = min(r - i, z[i - l]);

        while (s[z[i]] == s[i + z[i]])
            z[i]++;

        if (z[i] > r) {
            l = i;
            r = z[i];
        }
    }

    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    reverse(s.begin(), s.end());
    vector<int> z = getZ(s);

    int m;
    cin >> m;
    while (m--) {
        int i;
        cin >> i;
        cout << z[n - i] << '\n';
    }
}