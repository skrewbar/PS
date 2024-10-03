#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

vector<vector<ll>> tree;
vector<ll> arr;
int n, q;

void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = {arr[start]};
        return;
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        vector<ll> leftVector = tree[node*2];
        vector<ll> rightVector = tree[node*2+1];
        tree[node] = vector<ll>(leftVector.size() + rightVector.size());
        merge(
            leftVector.begin(), leftVector.end(),
            rightVector.begin(), rightVector.end(),
            tree[node].begin()
            );
    }
}


ll getBiggerNumCount(int node, int start, int end, int left, int right, ll criterion) {
    if (right < start or end < left) {
        return 0;
    } else if (left <= start and end <= right) {
        return tree[node].size() - (upper_bound(tree[node].begin(), tree[node].end(), criterion) - tree[node].begin());
    }
    ll lcount = getBiggerNumCount(node*2, start, (start+end)/2, left, right, criterion);
    ll rcount = getBiggerNumCount(node*2+1, (start+end)/2+1, end, left, right, criterion);
    return lcount + rcount;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    arr = vector<ll>(n, 0);

    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }

    int height = (int)ceil(log2(n));
    tree = vector<vector<ll>>(1 << (height + 1));
    init(1, 0, arr.size()-1);

    cin >> q;
    ll last_ans = 0;
    while (q--) {
        int a, b, c, i, j, k;
        cin >> a >> b >> c;
        i = (a ^ last_ans) - 1;
        j = (b ^ last_ans) - 1;
        k = (c ^ last_ans);
        last_ans = getBiggerNumCount(1, 0, arr.size()-1, i, j, k);
        cout << last_ans << '\n';
    }

    return 0;
}