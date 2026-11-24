#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void add(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    int getRangeSum(int l, int r) {
        int ret = 0;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret += t[l++];
            if (~r & 1)
                ret += t[r--];
        }

        return ret;
    }
};

vector<int> lo[101010];
vector<int> childs[101010];
int parent[101010][18], age[101010], answer[101010];

void initSparseTable(int cur) {
    for (int child : childs[cur]) {
        parent[child][0] = cur;
        for (int k = 1; k < 18; k++)
            parent[child][k] = parent[parent[child][k - 1]][k - 1];

        initSparseTable(child);
    }
}

void dfs(int cur, SegmentTree& seg) {
    for (int l : lo[cur])
        seg.add(l, 1);

    answer[cur] = seg.getRangeSum(0, age[cur]);

    for (int child : childs[cur])
        dfs(child, seg);

    for (int l : lo[cur])
        seg.add(l, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    fill(parent[1], parent[1] + 18, 1);
    for (int i = 1; i <= N; i++) {
        cin >> age[i] >> parent[i][0];

        if (i > 1)
            childs[parent[i][0]].push_back(i);
    }

    initSparseTable(1);

    for (int i = 0; i < M; i++) {
        int O, L, R;
        cin >> O >> L >> R;

        while (O != 1 and age[parent[O][0]] <= R) {
            int k = 17;

            while (age[parent[O][k]] > R)
                k--;

            O = parent[O][k];
        }

        lo[O].push_back(L);
    }

    SegmentTree seg(2e5);
    dfs(1, seg);

    for (int i = 1; i <= N; i++)
        print("{} ", answer[i]);

    return 0;
}