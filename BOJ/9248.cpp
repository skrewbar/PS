#include <bits/stdc++.h>
using namespace std;

vector<int> getSuffixArray(const string& s) {
    int n = (int)s.size();
    vector<int> sa(n);
    for (int i = 0; i < n; i++)
        sa[i] = i;
    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[i] = s[i] - 'a';

    int k = 1;
    auto compare = [&rank, &k, &n](int i, int j) {
        if (rank[i] != rank[j])
            return rank[i] < rank[j];

        int iRank = i + k < n ? rank[i + k] : -1;
        int jRank = j + k < n ? rank[j + k] : -1;
        return iRank < jRank;
    };

    while (k < n) {
        ranges::sort(sa, compare);
        vector<int> newRank(n);
        for (int i = 1; i < n; i++) {
            if (compare(sa[i - 1], sa[i]))
                newRank[sa[i]] = newRank[sa[i - 1]] + 1;
            else
                newRank[sa[i]] = newRank[sa[i - 1]];
        }

        k <<= 1;
        rank = newRank;
    }

    return sa;
}

vector<int> getLCPArray(const string& s, const vector<int>& sa) {
    int n = (int)s.size();
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

    vector<int> sa = getSuffixArray(s);
    vector<int> lcp = getLCPArray(s, sa);

    for (int i : sa)
        cout << i + 1 << ' ';
    cout << '\n';
    cout << "x ";
    for (int i = 1; i < lcp.size(); i++)
        cout << lcp[i] << ' ';
}