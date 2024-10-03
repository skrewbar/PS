#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;
using ll = long long int;

void changeValue(vector<int> &tree, int node, int start, int end, int index, int value) {
    if (index < start or end < index) {
        return;
    } else if (start == end) {
        tree[node] = value;
        return;
    } else {
        changeValue(tree, node*2, start, (start+end)/2, index, value);
        changeValue(tree, node*2+1, (start+end)/2+1, end, index, value);
        tree[node] = tree[node*2] + tree[node*2+1];
        return;
    }
}

ll getRangeSum(vector<int> &tree, int node, int start, int end, int left, int right) {
    if (right < start or end < left) {
        return 0;
    } else if (left <= start and end <= right) {
        return tree[node];
    } else {
        ll lsum = getRangeSum(tree, node*2, start, (start+end)/2, left, right);
        ll rsum = getRangeSum(tree, node*2+1, (start+end)/2+1, end, left, right);
        return lsum + rsum;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<int, int> match;
    vector<int> link(n);
    for (int i = 0 ; i < n ; i++) {
        int num;
        cin >> num;
        match[num] = i;
    }
    for (int i = 0 ; i < n ; i++) {
        int num;
        cin >> num;
        link[match[num]] = i;
    }

    int height = (int)ceil(log2(n));
    vector<int> tree(1 << (height + 1), 0);
    ll ans = 0;
    for (int i = 0 ; i < n ; i++) {
        ans += getRangeSum(tree, 1, 0, n-1, link[i]+1, n-1);
        changeValue(tree, 1, 0, n-1, link[i], 1);
    }

    cout << ans;
    return 0;
}