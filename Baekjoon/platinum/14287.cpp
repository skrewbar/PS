#include <bits/stdc++.h>
using namespace std;

int tourNum[100001];
int maxChild[100001];
vector<int> childs[100001];
int visitOrder = 0;


void eulerTour(int x) {
    tourNum[x] = ++visitOrder;

    for (int child : childs[x]) {
        eulerTour(child);
    }

    maxChild[x] = visitOrder;
}


struct SegmentTree {
    int tree[262144];

    SegmentTree() {
        fill(tree, tree+262144, 0);
    }


    void add(int node, int start, int end, int index, int value) {
        if (index < start or end < index) return;
        if (start == end) {
            tree[node] += value;
            return;
        }
        add(node*2, start, (start+end)/2, index, value);
        add(node*2+1, (start+end)/2+1, end, index, value);
        tree[node] = tree[node*2] + tree[node*2+1];
    }


    int getRangeSum(int node, int start, int end, int left, int right) {
        if (right < start or end < left) return 0;
        if (left <= start and end <= right) return tree[node];
        int leftSum = getRangeSum(node*2, start, (start+end)/2, left, right);
        int rightSum = getRangeSum(node*2+1, (start+end)/2+1, end, left, right);
        return leftSum + rightSum;
    }
} segmentTree;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;
    
    int parent;
    cin >> parent;
    for (int i = 2 ; i <= n ; i++) {
        cin >> parent;
        childs[parent].push_back(i);
    }
    eulerTour(1);


    while (m--) {
        int query, i;
        cin >> query >> i;
        
        if (query == 1) {
            int w;
            cin >> w;
            segmentTree.add(1, 1, n, tourNum[i], w);
        } else {
            cout << segmentTree.getRangeSum(1, 1, n, tourNum[i], maxChild[i]) << '\n';
        }
    }

    return 0;
}