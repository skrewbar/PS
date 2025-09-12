#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

int sqrtN;

struct Query {
    ll idx, l, r;

    bool operator<(const Query& q) {
        if (l / sqrtN != q.l / sqrtN)
            return l / sqrtN < q.l / sqrtN;
        return r < q.r;
    }
} queries[100'100];

int A[100'100], ans[100'100];
int distCnt[111'111], positiveCnt[400];

deque<int> queues[100'000];

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
    for (int i = sqrtN; i >= 0; i--) {
        if (positiveCnt[i]) {
            for (int j = (i + 1) * sqrtN - 1; j >= i * sqrtN; j--) {
                if (distCnt[j])
                    return j;
            }
        }
    }

    ASSERT(false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    sqrtN = ceil(sqrt(N));

    for (int i = 1; i <= N; i++)
        cin >> A[i];

    int M;
    cin >> M;
    for (int i = 1; i <= M; i++) {
        auto& [idx, l, r] = queries[i];
        idx = i;
        cin >> l >> r;
    }

    sort(queries, queries + M);
    int l, r;
    l = r = (queries[1].l + queries[1].r) >> 1;
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