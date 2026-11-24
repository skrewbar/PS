#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

vector<int> getSuffixArray(const string& s) {
    int n = s.size();

    vector<int> sa(n), newSa(n), rank(n), newRank(n);
    for (int i = 0; i < n; i++)
        sa[i] = i;

    ranges::sort(sa, [&](int i, int j) { return s[i] < s[j]; });

    for (int i = 1; i < n; i++) {
        rank[sa[i]] = rank[sa[i - 1]];
        if (s[sa[i]] != s[sa[i - 1]])
            rank[sa[i]]++;
    }

    vector<int> cnt(n);
    for (int len = 1; rank[sa[n - 1]] != n - 1; len <<= 1) {
        ranges::fill(cnt, 0);
        for (int i = 0; i < n; i++)
            cnt[rank[sa[i]]]++;
        for (int i = 1; i < (int)cnt.size(); i++)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            if (sa[i] - len >= 0)
                newSa[--cnt[rank[sa[i] - len]]] = sa[i] - len;
        for (int i = n - 1; i >= 0; i--)
            if (sa[i] + len >= n)
                newSa[--cnt[rank[sa[i]]]] = sa[i];

        swap(sa, newSa);

        auto compare = [&](int i, int j) {
            if (rank[i] != rank[j])
                return rank[i] < rank[j];
            return (i + len < n ? rank[i + len] : -1) <
                   (j + len < n ? rank[j + len] : -1);
        };

        newRank[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            newRank[sa[i]] = newRank[sa[i - 1]] + compare(sa[i - 1], sa[i]);

        swap(rank, newRank);
    }

    return sa;
}

vector<int> getLCPArray(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> lcp(n);

    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    int len = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == 0)
            continue;

        int j = sa[rank[i] - 1];
        while (i + len < n and j + len < n and s[i + len] == s[j + len])
            len++;

        lcp[rank[i]] = len ? len-- : 0;
    }

    return lcp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    ll n = s.size();

    vector<int> sa = getSuffixArray(s);
    vector<int> lcp = getLCPArray(s, sa);

    ll answer = n * (n + 1) / 2;
    for (int i = 1; i < n; i++)
        answer -= lcp[i];

    cout << answer;

    return 0;
}