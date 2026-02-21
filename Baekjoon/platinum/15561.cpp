#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

struct SegmentTree {
    struct Node {
        int sum, leftMax, rightMax, rangeMax;

        Node() : sum(0), leftMax(-INF), rightMax(-INF), rangeMax(-INF) {};

        Node(int value)
            : sum(value), leftMax(value), rightMax(value), rangeMax(value) {}

        static Node merge(const Node& left, const Node& right) {
            Node ret;

            ret.sum = left.sum + right.sum;
            ret.leftMax = max(left.leftMax, left.sum + right.leftMax);
            ret.rightMax = max(right.rightMax, left.rightMax + right.sum);
            ret.rangeMax = max(
                {left.rangeMax, right.rangeMax, left.rightMax + right.leftMax});

            return ret;
        }
    };

    int n;
    vector<Node> t;

    SegmentTree(int _n) : n(1 << (int)ceil(log2(_n))), t(n << 1) {}

    void modify(int i, int v) {
        t[i += n] = Node(v);
        for (i >>= 1; i > 0; i >>= 1)
            t[i] = Node::merge(t[i << 1], t[i << 1 | 1]);
    }

    int getMaxSubSum(int l, int r) {
        Node leftRes, rightRes;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                leftRes = Node::merge(leftRes, t[l++]);
            if (~r & 1)
                rightRes = Node::merge(t[r--], rightRes);
        }

        return Node::merge(leftRes, rightRes).rangeMax;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q, U, V;
    cin >> N >> Q >> U >> V;

    SegmentTree segTree(N + 1);

    for (int i = 1; i <= N; i++) {
        int K_i;
        cin >> K_i;

        segTree.modify(i, U * K_i + V);
    }

    while (Q--) {
        int C, A, B;
        cin >> C >> A >> B;

        if (C == 0)
            println("{}", (segTree.getMaxSubSum(A, B) - V));
        else
            segTree.modify(A, U * B + V);
    }

    return 0;
}