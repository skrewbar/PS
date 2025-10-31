#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct OrderStatisticTree {
    int maxValue;
    vector<int> t;

    OrderStatisticTree(int _maxValue) : maxValue(_maxValue) {
        int height = ceil(log2(maxValue)) + 1;
        t.resize(1 << height);
    }

    int size() { return t[1]; }

    void insert(int x) { insert(1, 1, maxValue, x); }
    void insert(int node, int s, int e, int i) {
        if (s == e) {
            t[node] = 1;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m)
            insert(node << 1, s, m, i);
        else
            insert(node << 1 | 1, m + 1, e, i);

        t[node] = t[node << 1] + t[node << 1 | 1];
    }

    void erase(int x) { erase(1, 1, maxValue, x); }
    void erase(int node, int s, int e, int i) {
        if (s == e) {
            t[node] = 0;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m)
            erase(node << 1, s, m, i);
        else
            erase(node << 1 | 1, m + 1, e, i);

        t[node] = t[node << 1] + t[node << 1 | 1];
    }

    bool contains(int x) { return contains(1, 1, maxValue, x); }
    bool contains(int node, int s, int e, int i) {
        if (s == e)
            return t[node] == 1;

        int m = (s + e) >> 1;
        if (i <= m)
            return contains(node << 1, s, m, i);
        else
            return contains(node << 1 | 1, m + 1, e, i);
    }

    int kth(int k) { return kth(1, 1, maxValue, k); }
    int kth(int node, int s, int e, int k) {
        if (s == e)
            return s;

        int m = (s + e) >> 1;
        if (k <= t[node << 1])
            return kth(node << 1, s, m, k);
        else
            return kth(node << 1 | 1, m + 1, e, k - t[node << 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int mid = -1;
    OrderStatisticTree left(N), right(N);

    for (int i = 1; i <= N / 2; i++)
        left.insert(i);

    if (N & 1)
        mid = N / 2 + 1;
    else
        right.insert(N / 2 + 1);

    for (int i = N / 2 + 2; i <= N; i++)
        right.insert(i);

    while (M--) {
        int tp, x;
        cin >> tp >> x;

        if (tp == 1) {
            if (left.contains(x)) {
                left.erase(x);
                if (mid != -1) {
                    left.insert(mid);
                    mid = -1;
                }
            } else if (right.contains(x)) {
                right.erase(x);
                if (mid != -1) {
                    right.insert(mid);
                    mid = -1;
                }
            } else {
                mid = -1;
            }

        } else {
            if (mid != -1)
                println("{}", x);
            else if (x <= left.size())
                println("{}", left.kth(x));
            else if (N - right.size() + 1 <= x)
                println("{}", right.kth(right.size() - (N - x + 1) + 1));
            else
                println("0");
        }
    }

    return 0;
}