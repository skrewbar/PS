#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getSuffixArray(const string& s) {
    int n = s.size();

    vector<int> sa(n);
    for (int i = 0; i < n; i++)
        sa[i] = i;
    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[i] = s[i] - 'a';

    int k = 1;

    auto compare = [&](int i, int j) {
        if (rank[i] != rank[j])
            return rank[i] < rank[j];
        return (i + k < n ? rank[i + k] : -1) < (j + k < n ? rank[j + k] : -1);
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

    string a, b;
    cin >> a >> b;
    string concat = a + '*' + b;

    vector<int> sa = getSuffixArray(concat);
    vector<int> lcp = getLCPArray(concat, sa);

    pair<int, int> answer(0, 0);  // (len, start)
    for (int i = 1; i < (int)concat.size(); i++) {
        if (sa[i - 1] < (int)a.size() ^ (int) a.size() < sa[i])
            continue;
        if (answer.first >= lcp[i])
            continue;
        answer.first = lcp[i];
        answer.second = sa[i];
    }

    cout << answer.first << '\n';
    for (int i = answer.second; i < answer.first + answer.second; i++)
        cout << concat[i];

    return 0;
}