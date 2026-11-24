#include <bits/stdc++.h>
#include <algorithm>

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

    int n;
    cin >> n;
    root = sqrt(n);
    // 배열 입력
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    // 정렬하고 중복 제거
    vector<int> values = arr;
    ranges::sort(values);
    values.erase(unique(values.begin(), values.end()), values.end());
    // 값 압축
    vector<int> cnt(values.size());
    for (int i = 0; i < n; i++)
        arr[i] = ranges::lower_bound(values, arr[i]) - values.begin();

    // 쿼리 입력
    int q;
    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        auto& [s, e, order] = queries[i];
        order = i;
        cin >> s >> e;
        s--, e--;
    }
    sort(queries.begin(), queries.end());

    // 답 구하기
    vector<int> answers(q);
    int s, e, answer = 1;
    s = e = (queries[0].s + queries[0].e) / 2;
    cnt[arr[s]]++;
    for (Query q : queries) {
        while (s < q.s)
            if (--cnt[arr[s++]] == 0)
                answer--;
        while (s > q.s)
            if (cnt[arr[--s]]++ == 0)
                answer++;

        while (e < q.e)
            if (cnt[arr[++e]]++ == 0)
                answer++;
        while (e > q.e)
            if (--cnt[arr[e--]] == 0)
                answer--;

        answers[q.order] = answer;
    }

    for (int i : answers)
        cout << i << '\n';

    return 0;
}