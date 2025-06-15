#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int root;

struct Query {
    int s, e, order;

    bool operator<(const Query& q) const {
        if (s / root != q.s / root)
            return s / root < q.s / root;
        return e < q.e;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> cnt(1'000'001);

    int n;
    cin >> n;
    root = sqrt(n);

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int m;
    cin >> m;
    vector<Query> queries(m);
    vector<int> answers(m);
    for (int i = 0; i < m; i++) {
        auto& [s, e, order] = queries[i];
        order = i;
        cin >> s >> e;
        s--, e--;
    }
    sort(queries.begin(), queries.end());

    int s, e, answer = 1;
    s = e = (queries[0].s + queries[0].e) / 2;
    cnt[a[s]]++;
    for (Query q : queries) {
        while (s < q.s)
            if (--cnt[a[s++]] == 0)
                answer--;

        while (q.s < s)
            if (cnt[a[--s]]++ == 0)
                answer++;

        while (e < q.e)
            if (cnt[a[++e]]++ == 0)
                answer++;

        while (q.e < e)
            if (--cnt[a[e--]] == 0)
                answer--;

        answers[q.order] = answer;
    }

    for (int i = 0; i < m; i++)
        cout << answers[i] << '\n';

    return 0;
}