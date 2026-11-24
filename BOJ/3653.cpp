#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}


class SegmentTree {
private:
    vector<int> tree;
    int lastIndex;

    void init(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        init(arr, node*2, start, (start+end)/2);
        init(arr, node*2+1, (start+end)/2+1, end);
        tree[node] = tree[node*2] + tree[node*2+1];
    }


    void changeValue(int node, int start, int end, int index, int value) {
        if (index < start or end < index) return;
        if (start == end) {
            tree[node] = value;
            return;
        }
        changeValue(node*2, start, (start+end)/2, index, value);
        changeValue(node*2+1, (start+end)/2+1, end, index, value);
        tree[node] = tree[node*2] + tree[node*2+1];
    }


    int getRangeSum(int node, int start, int end, int left, int right) {
        if (right < start or end < left) return 0;
        if (left <= start and end <= right) return tree[node];
        int lsum = getRangeSum(node*2, start, (start+end)/2, left, right);
        int rsum = getRangeSum(node*2+1, (start+end)/2+1, end, left, right);
        return lsum + rsum;
    }
public:

    SegmentTree(vector<int> &arr) : lastIndex(arr.size()-1) {
        int height = (int) ceil(log2(arr.size()));
        tree.resize(1 << (height + 1));
        init(arr, 1, 0, arr.size() - 1);
    }


    void changeValue(int index, int value) {
        changeValue(1, 0, lastIndex, index, value);
    }

    int getRangeSum(int left, int right) {
        return getRangeSum(1, 0, lastIndex, left, right);
    }
};


int main() {
    fastio();

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        int lastLoc = n - 1;

        vector<int> arr(n+m);
        vector<int> location(n+1);

        for (int i = 1; i <= n; i++) {
            location[i] = n - i;
            arr[location[i]] = 1;
        }

        SegmentTree segmentTree(arr);

        while (m--) {
            int q;
            cin >> q;

            cout << segmentTree.getRangeSum(location[q], arr.size()-1) - 1 << ' ';

            segmentTree.changeValue(location[q], 0);
            location[q] = ++lastLoc;
            segmentTree.changeValue(location[q], 1);
        }

        cout << '\n';
    }

    return 0;
}