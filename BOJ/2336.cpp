#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

void minify(int& x, int v) {
    x = min(x, v);
}

struct MinSegmentTree {
    int n;
    vector<int> t;

    MinSegmentTree(int n) : n(n), t(n << 1, INF) {}

    void modify(int i, int v) {
        for (minify(t[i += n], v); i > 1; i >>= 1)
            t[i >> 1] = min(t[i], t[i ^ 1]);
    }

    int getRangeMin(int l, int r) {
        int ret = INF;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                minify(ret, t[l++]);
            if (~r & 1)
                minify(ret, t[r--]);
        }
        return ret;
    }
};

struct Student {
    int rank[4];
} students[500'500];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    MinSegmentTree tree(n + 1);
    for (int j = 1; j <= 3; j++)
        for (int i = 1; i <= n; i++) {
            int student;
            cin >> student;
            students[student].rank[j] = i;
        }

    sort(students + 1, students + n + 1,
         [&](const Student& s1, const Student& s2) {
             return s1.rank[1] < s2.rank[1];
         });

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        Student student = students[i];
        if (tree.getRangeMin(0, student.rank[2] - 1) > student.rank[3])
            answer++;
        tree.modify(student.rank[2], student.rank[3]);
    }

    print("{}", answer);
    return 0;
}