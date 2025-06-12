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

    vector<int> sa(n);
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i] - 'a' + 1;
    }

    int k = 1;
    auto compare = [&](const int i, const int j) {
        if (rank[i] != rank[j])
            return rank[i] < rank[j];

        int rank_i = i + k < n ? rank[i + k] : -1;
        int rank_j = j + k < n ? rank[j + k] : -1;
        return rank_i < rank_j;
    };

    vector<int> newRank(n);
    while (k < n) {
        ranges::sort(sa, compare);

        newRank[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            newRank[sa[i]] = newRank[sa[i - 1]] + compare(sa[i - 1], sa[i]);
        }

        rank = newRank;
        k <<= 1;
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