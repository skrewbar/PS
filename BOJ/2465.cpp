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

    SegmentTree(int _n) {
        n = 1 << (int)ceil(log2(_n));
        t.assign(n << 1, 0);
    }

    void add(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1)
            t[i >> 1] = t[i] + t[i ^ 1];
    }

    // k: zero based
    int getKth(int k) {
        int i = 1;
        while (i < n) {
            if (t[i << 1] > k) {
                i = i << 1;
            } else {
                k -= t[i << 1];
                i = i << 1 | 1;
            }
        }

        return i - n;
    }
};

template <typename T>
struct Compressor {
    vector<T> v;

    Compressor(const vector<T>& _v) : v(_v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    int getRankOf(T x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    }

    T at(size_t idx) { return v[idx]; }

    size_t size() { return v.size(); }
};

int S[101010], heights[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> heightSet(N);
    for (int i = 0; i < N; i++)
        cin >> heightSet[i];

    Compressor<int> compressor(heightSet);
    SegmentTree segTree(compressor.size());

    for (int i = 0; i < N; i++)
        segTree.add(compressor.getRankOf(heightSet[i]), 1);
    
    for (int i = 0; i < N; i++)
        cin >> S[i];

    for (int i = N - 1; i >= 0; i--) {
        int idx = segTree.getKth(S[i]);
        heights[i] = compressor.at(idx);
        segTree.add(idx, -1);
    }

    for (int i = 0; i < N; i++)
        cout << heights[i] << '\n';

    return 0;
}