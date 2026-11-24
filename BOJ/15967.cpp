#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void init(vector<long long> &seq, vector<long long> &tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = seq[start];
    } else {
        init(seq, tree, node*2, start, (start+end)/2);
        init(seq, tree, node*2+1, (start+end)/2+1, end);
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}


void update_lazy(vector<long long> &tree, vector<long long> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}


void update_range(vector<long long> &tree, vector<long long> &lazy, int node, int start, int end, int left, int right, long long val) {
    update_lazy(tree, lazy, node, start, end);
    if (right < start || end < left) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    update_range(tree, lazy, node*2, start, (start+end)/2, left, right, val);
    update_range(tree, lazy, node*2+1, (start+end)/2+1, end, left, right, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}


long long get_range_sum(vector<long long> &tree, vector<long long> &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (right < start || end < left) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    long long lsum = get_range_sum(tree, lazy, node*2, start, (start+end)/2, left, right);
    long long rsum = get_range_sum(tree, lazy, node*2+1, (start+end)/2+1, end, left, right);
    return lsum + rsum;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q1, q2;
    cin >> n >> q1 >> q2;
    q1 += q2;

    vector<long long> seq(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> seq[i];
    }
    int h = (int)ceil(log2(n));
    int tree_size = 1 << (h + 1);
    vector<long long> tree(tree_size, 0);
    vector<long long> lazy(tree_size, 0);
    init(seq, tree, 1, 0, n-1);

    while (q1--) {
        int query;
        cin >> query;

        if (query == 1) {
            int left, right;
            cin >> left >> right;
            cout << get_range_sum(tree, lazy, 1, 0, n-1, left-1, right-1) << '\n';
        } else {
            int left, right;
            long long val;
            cin >> left >> right >> val;
            update_range(tree, lazy, 1, 0, n-1, left-1, right-1, val);
        }
    }

    return 0;
}