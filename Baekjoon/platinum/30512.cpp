#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int INF = 1e9;

struct RUPQSegmentTree {
    vector<pair<int, int>> t;  // (query, queryNumber)

    RUPQSegmentTree(const vector<int>& arr) {
        int height = ceil(log2(arr.size() - 1)) + 1;
        t = vector(1 << height, pair(INF, 0));
        init(arr, 1, 1, arr.size() - 1);
    }

    void init(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            t[node] = pair(arr[start], 0);
            return;
        }

        int mid = (start + end) >> 1;
        init(arr, node << 1, start, mid);
        init(arr, node << 1 | 1, mid + 1, end);
    }

    void updateRange(int node,
                     int start,
                     int end,
                     int left,
                     int right,
                     int query,
                     int queryNumber) {
        if (right < start or end < left)
            return;
        if (left <= start and end <= right) {
            if (query < t[node].first) {
                t[node] = pair(query, queryNumber);
            }
            return;
        }

        int mid = (start + end) >> 1;
        updateRange(node << 1, start, mid, left, right, query, queryNumber);
        updateRange(node << 1 | 1, mid + 1, end, left, right, query,
                    queryNumber);
    }

    pair<int, int> pointQuery(int node, int start, int end, int index) {
        if (start == end) {
            return t[node];
        }

        int mid = (start + end) >> 1;
        pair<int, int> res;
        if (index <= mid)
            res = pointQuery(node << 1, start, mid, index);
        else
            res = pointQuery(node << 1 | 1, mid + 1, end, index);

        if (t[node].first < res.first)
            res = t[node];
        if (t[node].first == res.first)
            res.second = min(res.second, t[node].second);

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    RUPQSegmentTree segTree(A);

    int Q;
    cin >> Q;
    vector<int> D(Q + 1);
    for (int queryNumber = 1; queryNumber <= Q; queryNumber++) {
        int left, right, query;
        cin >> left >> right >> query;
        segTree.updateRange(1, 1, N, left, right, query, queryNumber);
    }

    for (int i = 1; i <= N; i++) {
        pair<int, int> lastQuery = segTree.pointQuery(1, 1, N, i);
        cout << lastQuery.first << ' ';
        D[lastQuery.second]++;
    }

    cout << '\n';

    for (int i = 1; i <= Q; i++) {
        cout << (D[i] += D[i - 1]) << ' ';
    }

    return 0;
}