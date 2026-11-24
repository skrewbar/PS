#include <bits/stdc++.h>
using namespace std;

int tourNum[100001];
int maxChild[100001];
vector<int> childs[100001];
int visitOrder = 0;


void eulerTour(int v) {
    tourNum[v] = ++visitOrder;

    for (int child : childs[v]) {
        eulerTour(child);
    }

    maxChild[v] = visitOrder;
}


struct SegmentTree {
    int tree[262144];

    void addRange(int node, int start, int end, int left, int right, int value) {
        if (right < start or end < left) return;
        if (left <= start and end <= right) tree[node] += value;
        else {
            addRange(node*2, start, (start+end)/2, left, right, value);
            addRange(node*2+1, (start+end)/2+1, end, left, right, value);
        }
    }


    int getPraise(int node, int start, int end, int index) {
        if (start == end) return tree[node];
        if (index <= (start+end)/2) {
            return getPraise(node*2, start, (start+end)/2, index) + tree[node];
        } else {
            return getPraise(node*2+1, (start+end)/2+1, end, index) + tree[node];
        }
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
            segmentTree.addRange(1, 1, n, tourNum[i], maxChild[i], w);
        } else {
            cout << segmentTree.getPraise(1, 1, n, tourNum[i]) << '\n';
        }
    }

    return 0;
}