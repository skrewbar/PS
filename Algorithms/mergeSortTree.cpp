// 세그먼트 트리의 활용
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;

void init(vector<vector<ll>> &tree, vector<ll> &arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = vector<ll>({arr[start]});
        return;
    } else {
        init(tree, arr, node*2, start, (start+end)/2);
        init(tree, arr, node*2+1, (start+end)/2+1, end);
        vector<ll> leftVector = tree[node*2];
        vector<ll> rightVector = tree[node*2+1];
        tree[node] = vector<ll>(leftVector.size() + rightVector.size());
        merge(leftVector.begin(), leftVector.end(), rightVector.begin(), rightVector.end(), tree[node].begin());
    }
}

ll getBiggerNumCount(vector<vector<ll>> &tree, int node, int start, int end, int left, int right, ll criterion) {
    if (right < start or end < left) {
        return 0;
    } else if (left <= start and end <= right) {
        return tree[node].size() - (upper_bound(tree[node].begin(), tree[node].end(), criterion) - tree[node].begin());
    }
    ll lcount = getBiggerNumCount(tree, node*2, start, (start+end)/2, left, right, criterion);
    ll rcount = getBiggerNumCount(tree, node*2+1, (start+end)/2+1, end, left, right, criterion);
    return lcount + rcount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> v({5, 4, 6, 7, 3, 8, 2, 1, 10, 9});

    vector<vector<ll>> tree(2048);
    init(tree, v, 1, 0, 9);
    
    cout << getBiggerNumCount(tree, 1, 0, 9, 0, 9, 0);

    return 0;
}