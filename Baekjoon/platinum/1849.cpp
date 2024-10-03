#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


void init(vector<int> &tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = 1;
        return;
    }
    init(tree, node*2, start, (start+end)/2);
    init(tree, node*2+1, (start+end)/2+1, end);
    tree[node] = tree[node*2] + tree[node*2+1];
    return;
}

void changeToZero(vector<int> &tree, int node, int start, int end, int index) {
    if (index < start or end < index) {
        return;
    }
    if (start == end) {
        tree[node] = 0;
        return;
    }
    changeToZero(tree, node*2, start, (start+end)/2, index);
    changeToZero(tree, node*2+1, (start+end)/2+1, end, index);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int getRangeSum(vector<int> &tree, int node, int start, int end, int left, int right) {
    if (right < start or end < left) {
        return 0;
    }
    if (left <= start and end <= right) {
        return tree[node];
    }
    int lsum = getRangeSum(tree, node*2, start, (start+end)/2, left, right);
    int rsum = getRangeSum(tree, node*2+1, (start+end)/2+1, end, left, right);
    return lsum + rsum;
}

int findIndex(vector<int> &tree, int node, int start, int end, int blankCount) {
    if (start == end) {
        return start;
    }
    if (blankCount <= tree[node*2]) {
        return findIndex(tree, node*2, start, (start+end)/2, blankCount);
    }
    return findIndex(tree, node*2+1, (start+end)/2+1, end, blankCount - tree[node*2]);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> array(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> array[i];
    }

    int treeHeight = (int)ceil(log2(n));
    vector<int> tree((1 << (treeHeight + 1)), 0);
    init(tree, 1, 0, n-1);

    vector<int> answer(n, 0);
    for (int i = 0 ; i < n ; i++) {
        int index = findIndex(tree, 1, 0, n-1, array[i]+1);
        answer[index] = i+1;
        changeToZero(tree, 1, 0, n-1, index);
    }

    for (int i = 0 ; i < n ; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}