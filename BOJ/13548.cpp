#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int n, root;

struct Query {
    int s, e, order;

    bool operator<(const Query& q) {
        if (s / root != q.s / root)
            return s / root < q.s / root;
        return e < q.e;
    }
};

vector<int> cnt, cntOfCnt;
int res = 0;
void add(int v) {
    cntOfCnt[cnt[v]++]--;
    cntOfCnt[cnt[v]]++;
    res = max(res, cnt[v]);
}
void remove(int v) {
    if (--cntOfCnt[cnt[v]] == 0 and res == cnt[v])
        res--;
    cntOfCnt[--cnt[v]]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    root = sqrt(n);

    vector<int> arr(n);
    int max_elem = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        max_elem = max(max_elem, arr[i]);
    }
    cnt = vector(max_elem + 1, 0);
    cntOfCnt = vector(n + 1, 0);
    cntOfCnt[0] = max_elem;

    int m;
    cin >> m;
    vector<Query> queries(m);
    vector<int> answer(m);
    int i = 0;
    for (auto& [s, e, ord] : queries) {
        ord = i++;
        cin >> s >> e;
        s--, e--;
    }
    sort(queries.begin(), queries.end());

    int s, e;
    s = e = (queries[0].s + queries[0].e) / 2;
    add(arr[s]);

    for (const Query& q : queries) {
        while (s > q.s)
            add(arr[--s]);
        while (e < q.e)
            add(arr[++e]);

        while (s < q.s)
            remove(arr[s++]);
        while (e > q.e)
            remove(arr[e--]);

        answer[q.order] = res;
    }

    for (int i = 0; i < m; i++)
        cout << answer[i] << '\n';

    return 0;
}