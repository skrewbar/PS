#include <bits/stdc++.h>
using namespace std;

int tourNum[100001];
int maxChild[100001];
int visitOrder = 0;
vector<int> childs[100001];


void eulerTour(int x) {
    tourNum[x] = ++visitOrder;

    for (int child : childs[x]) {
        eulerTour(child);
    }

    maxChild[x] = visitOrder;
}


int tree[262144];
int lazy[262144];

void init(int node, int start, int end) {
    if (start == end) tree[node] = 1;
    else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

void updateLazy(int node, int start, int end) {
    if (lazy[node] != -1) {
        tree[node] = (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node*2] = lazy[node];
            lazy[node*2+1] = lazy[node];
        }
        lazy[node] = -1;
    }
}

void setRange(int node, int start, int end, int left, int right, int value) {
    updateLazy(node, start, end);
    if (right < start or end < left) return;
    if (left <= start and end <= right) {
        lazy[node] = value;
        updateLazy(node, start, end);
        return;
    }
    setRange(node*2, start, (start+end)/2, left, right, value);
    setRange(node*2+1, (start+end)/2+1, end, left, right, value);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int getRange(int node, int start, int end, int left, int right) {
    updateLazy(node, start, end);
    if (right < start or end < left) return 0;
    if (left <= start and end <= right) return tree[node];
    int lsum = getRange(node*2, start, (start+end)/2, left, right);
    int rsum = getRange(node*2+1, (start+end)/2+1, end, left, right);
    return lsum + rsum;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;

    int parent;
    cin >> parent;
    for (int i = 2 ; i <= n ; i++) {
        cin >> parent;
        childs[parent].push_back(i);
    }
    eulerTour(1);

    fill(lazy, lazy+262144, -1);
    init(1, 1, visitOrder);
    int m;
    cin >> m;
    while (m--) {
        int query, i;
        cin >> query >> i;

        if (query == 1) {
            if (tourNum[i] == maxChild[i]) continue;
            setRange(1, 1, visitOrder, tourNum[i]+1, maxChild[i], 1);
        } else if (query == 2) {
            if (tourNum[i] == maxChild[i]) continue;
            setRange(1, 1, visitOrder, tourNum[i]+1, maxChild[i], 0);
        } else {
            if (tourNum[i] == maxChild[i]) cout << 0 << '\n';
            else cout << getRange(1, 1, visitOrder, tourNum[i]+1, maxChild[i]) << '\n';
        }
    }


    return 0;
}