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


struct SumSegTree {
    int tree[300000];

    SumSegTree() {
        fill(tree, tree+300000, 0);
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
        
        int lsum = getRangeSum(node*2, start, (start+end)/2, left, right);
        int rsum = getRangeSum(node*2+1, (start+end)/2+1, end, left, right);
        return lsum + rsum;
    }
} sumSegTree;


struct PointSegTree {
    int tree[300000];

    PointSegTree() {
        fill(tree, tree+300000, 0);
    }


    void addRange(int node, int start, int end, int left, int right, int value) {
        if (right < start or end < left) return;
        if (left <= start and end <= right) {
            tree[node] += value;
            return;
        }
        addRange(node*2, start, (start+end)/2, left, right, value);
        addRange(node*2+1, (start+end)/2+1, end, left, right, value);
    }


    int get(int node, int start, int end, int index) {
        if (start == end) return tree[node];
        if (index <= (start+end)/2) return get(node*2, start, (start+end)/2, index) + tree[node];
        else return get(node*2+1, (start+end)/2+1, end, index) + tree[node];
    }
} pointSegTree;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    bool isSubDirecion = true;

    int n, m;
    cin >> n >> m;

    int parent = 0;
    cin >> parent;
    for (int i = 2 ; i <= n ; i++) {
        cin >> parent;
        childs[parent].push_back(i);
    }

    eulerTour(1);

    while (m--) {
        int query;
        cin >> query;

        if (query == 1) {
            int i, w;
            cin >> i >> w;

            if (isSubDirecion) pointSegTree.addRange(1, 1, n, tourNum[i], maxChild[i], w);
            else sumSegTree.add(1, 1, n, tourNum[i], w);
        } else if (query == 2) {
            int i;
            cin >> i;

            int sum = 0;
            sum += pointSegTree.get(1, 1, n, tourNum[i]);
            sum += sumSegTree.getRangeSum(1, 1, n, tourNum[i], maxChild[i]);
            cout << sum << '\n';
        } else {
            isSubDirecion ^= 1;
        }
    }



    return 0;
}