#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int sqrtN;

struct Query {
    int idx, l, r;

    bool operator<(const Query& q) {
        if (l / sqrtN != q.l / sqrtN)
            return l / sqrtN < q.l / sqrtN;
        return r < q.r;
    }
} queries[111'111];
int ans[111'111];

int A[111'111];
deque<int> queues[222'222];
int distCnt[222'222], positiveCnt[500];

void add(int idx) {
    deque<int>& q = queues[A[idx]];

    if (not q.empty()) {
        int dist = q.back() - q.front();
        if (--distCnt[dist] == 0)
            positiveCnt[dist / sqrtN]--;
    }

    if (q.empty())
        q.push_back(idx);
    else if (idx < q.front())
        q.push_front(idx);
    else
        q.push_back(idx);

    int dist = q.back() - q.front();
    if (distCnt[dist]++ == 0)
        positiveCnt[dist / sqrtN]++;
}

void remove(int idx) {
    deque<int>& q = queues[A[idx]];

    ASSERT(not q.empty());
    int dist = q.back() - q.front();
    if (--distCnt[dist] == 0)
        positiveCnt[dist / sqrtN]--;

    if (idx == q.front())
        q.pop_front();
    else
        q.pop_back();

    if (not q.empty()) {
        dist = q.back() - q.front();
        if (distCnt[dist]++ == 0)
            positiveCnt[dist / sqrtN]++;
    }
}

int getMaxDist() {
    for (int bucket = sqrtN; bucket >= 0; bucket--) {
        if (positiveCnt[bucket]) {
            for (int i = (bucket + 1) * sqrtN; i >= bucket * sqrtN; i--)
                if (distCnt[i])
                    return i;
        }
    }

    ASSERT(false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    sqrtN = ceil(sqrt(N));

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        A[i] += A[i - 1];
    }
    for (int i = 0; i <= N; i++)
        A[i] += N;

    int M;
    cin >> M;
    for (int i = 1; i <= M; i++) {
        auto& [idx, l, r] = queries[i];
        idx = i;
        cin >> l >> r;
        l--;
    }
    sort(queries + 1, queries + M + 1);

    int l, r;
    l = r = (queries[1].l + queries[1].r) / 2;
    add(l);
    for (int i = 1; i <= M; i++) {
        const Query& q = queries[i];

        while (q.l < l)
            add(--l);
        while (r < q.r)
            add(++r);

        while (l < q.l)
            remove(l++);
        while (q.r < r)
            remove(r--);

        ans[q.idx] = getMaxDist();
    }

    for (int i = 1; i <= M; i++)
        cout << ans[i] << '\n';

    return 0;
}