#include <bits/stdc++.h>
using namespace std;

vector<int> tree;
vector<int> lazy;

void lazyUpdate(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void rangeAdd(int node, int start, int end, int left, int right, int value) {
    lazyUpdate(node, start, end);
    if (right < start or end < left or right < left) {
        return;
    }
    if (left <= start and end <= right) {
        lazy[node] += value;
        lazyUpdate(node, start, end);
        return;
    }
    rangeAdd(node*2, start, (start+end)/2, left, right, value);
    rangeAdd(node*2+1, (start+end)/2+1, end, left, right, value);
}

void change(int node, int start, int end, int index, int value) {
    lazyUpdate(node, start, end);
    if (index < start or end < index) {
        return;
    }
    if (start == end) {
        tree[node] = value;
        return;
    }
    change(node*2, start, (start+end)/2, index, value);
    change(node*2+1, (start+end)/2+1, end, index, value);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int get(int node, int start, int end, int index) {
    lazyUpdate(node, start, end);
    if (index < start or end < index) {
        return 0;
    }
    if (start == end) {
        return tree[node];
    }
    int left = get(node*2, start, (start+end)/2, index);
    int right = get(node*2+1, (start+end)/2+1, end, index);
    return left + right;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n = 100000;
    int height = (int)ceil(log2(n));
    tree.resize(1 << (height + 1), 0);
    lazy.resize(1 << (height + 1), 0);

    int q; cin >> q;
    while (q--) {
        int left, right, leftFlower, rightFlower;
        cin >> left >> right;
        left--; right--;
        rangeAdd(1, 0, n-1, left+1, right-1, 1);
        leftFlower = get(1, 0, n-1, left);
        if (leftFlower > 0) change(1, 0, n-1, left, 0);
        rightFlower = get(1, 0, n-1, right);
        if (rightFlower > 0) change(1, 0, n-1, right, 0);
        cout << leftFlower + rightFlower << '\n';
    }


    return 0;
}