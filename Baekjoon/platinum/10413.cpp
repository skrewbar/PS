#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getSuffixArray(const string& s) {
    int n = s.size();

    vector<int> sa(n), nsa(n), rank(n), nrank(n), count(n);
    for (int i = 0; i < n; i++)
        sa[i] = i;

    sort(sa.begin(), sa.end(), [&](int i, int j) { return s[i] < s[j]; });
    for (int i = 1; i < n; i++)
        rank[sa[i]] = rank[sa[i - 1]] + (s[sa[i - 1]] < s[sa[i]]);

    for (int len = 1; rank[sa.back()] < n - 1; len <<= 1) {
        fill(count.begin(), count.end(), 0);
        for (int i = 0; i < n; i++)
            count[rank[sa[i]]]++;
        for (int i = 1; i < n; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            if (sa[i] - len >= 0)
                nsa[--count[rank[sa[i] - len]]] = sa[i] - len;
        for (int i = n - 1; i >= 0; i--)
            if (sa[i] + len >= n)
                nsa[--count[rank[sa[i]]]] = sa[i];

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

vector<int> getLCPArray(const string& s) {
    int n = s.size();

    vector<int> rank(n), lcp(n), sa = getSuffixArray(s);
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    for (int i = 0, len = 0; i < n; i++) {
        if (rank[i] == 0)
            continue;

        int j = sa[rank[i] - 1];
        while (i + len < n and j + len < n and s[i + len] == s[j + len])
            len++;

        lcp[rank[i]] = len > 0 ? len-- : 0;
    }

    return lcp;
}

void solve() {
    string s;
    cin >> s;

    vector<int> lcp = getLCPArray(s);
    int answer = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        answer += max(lcp[i] - lcp[i - 1], 0);
    }

    print("{}\n", answer);
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