#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int n) : n(n) {
        int height = ceil(log2(n)) + 1;
        t = vector(1 << height, 0);
    }

    void modify(int node, int start, int end, int index, int value) {
        if (index < start or end < index)
            return;
        if (start == end) {
            t[node] = value;
            return;
        }

        int mid = (start + end) >> 1;
        modify(node << 1, start, mid, index, value);
        modify(node << 1 | 1, mid + 1, end, index, value);
        t[node] = t[node << 1] + t[node << 1 | 1];
    }

    // 오른쪽부터 빈칸의 개수가 count인 인덱스를 반환
    int query(int node, int start, int end, int count) {
        if (start == end)
            return start;

        int mid = (start + end) >> 1;

        if (t[node << 1 | 1] >= count)
            return query(node << 1 | 1, mid + 1, end, count);
        else
            return query(node << 1, start, mid, count - t[node << 1 | 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> invSeq(n + 1), arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> invSeq[i];

    SegmentTree tree(n + 1);
    for (int i = 1; i <= n; i++)
        tree.modify(1, 1, n, i, 1);

    for (int i = n; i >= 1; i--) {
        int slot = tree.query(1, 1, n, invSeq[i] + 1);
        tree.modify(1, 1, n, slot, 0);
        ASSERT(arr[slot] == 0);
        arr[slot] = i;
    }

    for (int i = 1; i <= n; i++)
        print("{} ", arr[i]);

    return 0;
}