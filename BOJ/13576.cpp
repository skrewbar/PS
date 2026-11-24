#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getZArray(const string& s) {
    vector<int> z(s.size());
    z[0] = z.size();

    int l = 0, r = 0;
    for (int i = 1; i < (int)z.size(); i++) {
        if (i <= r)
            z[i] = min(r - i, z[i - l]);

        while (s[z[i]] == s[i + z[i]])
            z[i]++;

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
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

    vector<int> z = getZArray(s);
    vector<int> cntSuffixSum(n + 1);
    for (int i = 0; i < n; i++)
        cntSuffixSum[z[i]]++;
    for (int i = n - 1; i >= 0; i--)
        cntSuffixSum[i] += cntSuffixSum[i + 1];

    map<int, int> lenCntMap;
    for (int i = 0; i < n; i++) {
        if (i + z[i] == n)
            lenCntMap[z[i]] = cntSuffixSum[z[i]];
    }

    cout << lenCntMap.size() << '\n';
    for (auto [l, c] : lenCntMap)
        cout << l << ' ' << c << '\n';

    return 0;
}