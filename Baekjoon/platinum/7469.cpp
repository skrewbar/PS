#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tree;
vector<int> arr;
int n, m;


void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = {arr[start]};
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = vector<int>(tree[node*2].size() + tree[node*2+1].size());
        merge(
            tree[node*2].begin(), tree[node*2].end(),
            tree[node*2+1].begin(), tree[node*2+1].end(),
            tree[node].begin()
        );
    }
}

int getLessOrEqCount(int node, int start, int end, int left, int right, int value) {
    if (right < start or end < left) {
        return 0;
    } else if (left <= start and end <= right) {
        return upper_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
    }
    int leftCount = getLessOrEqCount(node*2, start, (start+end)/2, left, right, value);
    int rightCount = getLessOrEqCount(node*2+1, (start+end)/2+1, end, left, right, value);
    return leftCount + rightCount;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n >> m;
    arr = vector<int>(n, 0);
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }
    int height = (int)ceil(log2(n));
    tree = vector<vector<int>>(1 << (height + 1));
    init(1, 0, arr.size()-1);

    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        i--; j--;

        int left = -1e9, right = 1e9, mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (getLessOrEqCount(1, 0, arr.size()-1, i, j, mid) < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << left;
    }

    return 0;
}