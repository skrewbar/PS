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

    SegmentTree(int _n) : n(_n), t(n << 1) {}

    void modify(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1)
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> skill(N);
    for (int i = 0; i < N; i++)
        cin >> skill[i];

    vector<int> compressedSkill = skill;
    sort(compressedSkill.begin(), compressedSkill.end());
    compressedSkill.erase(
        unique(compressedSkill.begin(), compressedSkill.end()),
        compressedSkill.end());

    SegmentTree tree(N + 1);
    vector<int> ans(N);
    for (int i = 0; i < N; i++) {
        int s = lower_bound(compressedSkill.begin(), compressedSkill.end(),
                            skill[i]) -
                compressedSkill.begin();

        cout << tree.getRangeSum(s + 1, N) + 1 << '\n';
        tree.modify(s, 1);
    }

    return 0;
}