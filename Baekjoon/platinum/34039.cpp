#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

constexpr ll MAX_LEN = 100'100;

enum Query : uint8_t {
    CHANGE = 1,
    GET_MAX_SONG_CNT = 2,
    ADD_NEW_SONG = 3,
};

struct SegmentTree {
    vector<ll> cntTree, timeTree;
    int n;

    SegmentTree(int n) : n(n) {
        int height = (int)ceil(log2(n)) + 1;
        cntTree = timeTree = vector<ll>(1 << height);
    }

    void add(int length) { modify(1, 0, n - 1, length, true); }
    void remove(int length) { modify(1, 0, n - 1, length, false); }

    ll query(int node, int start, int end, ll t) {
        if (start == end)
            return min(t / start, cntTree[node]);

        int mid = (start + end) / 2;
        if (t <= timeTree[node << 1])
            return query(node << 1, start, mid, t);
        else
            return query(node << 1 | 1, mid + 1, end, t - timeTree[node << 1]) +
                   cntTree[node << 1];
    }

   private:
    void modify(int node, int start, int end, int length, bool add) {
        if (length < start or end < length)
            return;
        if (start == end) {
            if (add) {
                cntTree[node]++;
                timeTree[node] += length;
            } else {
                cntTree[node]--;
                timeTree[node] -= length;
            }
            return;
        }

        int mid = (start + end) / 2;
        modify(node << 1, start, mid, length, add);
        modify(node << 1 | 1, mid + 1, end, length, add);
        cntTree[node] = cntTree[node << 1] + cntTree[node << 1 | 1];
        timeTree[node] = timeTree[node << 1] + timeTree[node << 1 | 1];
    }
} segTree(MAX_LEN);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> length(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> length[i];
        segTree.add(length[i]);
    }

    while (q--) {
        int q;
        cin >> q;
        
        if (q == CHANGE) {
            int j, v;
            cin >> j >> v;
            segTree.remove(length[j]);
            length[j] = v;
            segTree.add(length[j]);
        }
        if (q == GET_MAX_SONG_CNT) {
            ll t;
            cin >> t;
            print("{}\n", segTree.query(1, 0, MAX_LEN - 1, t));
        }
        if (q == ADD_NEW_SONG) {
            int v;
            cin >> v;
            length.push_back(v);
            segTree.add(v);
        }
    }
    
    return 0;
}