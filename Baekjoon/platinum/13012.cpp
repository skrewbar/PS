#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getSuffixArray(const string& s) {
    int n = s.size();

    vector<int> sa(n), nsa(n), rank(n), nrank(n), cnt(n);
    for (int i = 0; i < n; i++)
        sa[i] = i;

    sort(sa.begin(), sa.end(), [&](int i, int j) { return s[i] < s[j]; });
    for (int i = 1; i < n; i++)
        rank[sa[i]] = rank[sa[i - 1]] + (s[sa[i - 1]] < s[sa[i]]);

    for (int len = 1; rank[sa.back()] < n - 1; len <<= 1) {
        fill(cnt.begin(), cnt.end(), 0);

        for (int i = 0; i < n; i++)
            cnt[rank[sa[i]]]++;
        for (int i = 1; i < n; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            if (sa[i] - len >= 0)
                nsa[--cnt[rank[sa[i] - len]]] = sa[i] - len;
        for (int i = n - 1; i >= 0; i--)
            if (sa[i] + len >= n)
                nsa[--cnt[rank[sa[i]]]] = sa[i];

        swap(sa, nsa);

        auto compare = [&](int i, int j) {
            if (rank[i] != rank[j])
                return rank[i] < rank[j];

            return (i + len < n ? rank[i + len] : -1) <
                   (j + len < n ? rank[j + len] : -1);
        };

        nrank[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            nrank[sa[i]] = nrank[sa[i - 1]] + compare(sa[i - 1], sa[i]);

        swap(rank, nrank);
    }

    return sa;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<int> sa = getSuffixArray(s);
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == 'a')
            continue;

        s[i]--;
        if (sa == getSuffixArray(s)) {
            print("1");
            return 0;
        }
        s[i]++;
    }

    print("0");
    return 0;
}