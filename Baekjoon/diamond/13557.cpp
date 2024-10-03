#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
struct Node {
    ll lmax, rmax, mmax, sum;
} tree[400000];
ll arr[100000];


Node tempNode() {
    return {(ll)-1e11, (ll)-1e11, (ll)-1e11, 0};
}


Node merge(Node left, Node right) {
    Node ret;
    ret.lmax = max(left.lmax, left.sum + right.lmax);
    ret.rmax = max(right.rmax, left.rmax + right.sum);
    ret.mmax = max({ret.lmax, ret.rmax, left.mmax, right.mmax, left.rmax+right.lmax});
    ret.sum = left.sum + right.sum;
    return ret;
}


void init(int node = 1, int start = 0, int end = n-1) {
    if (start == end) {
        tree[node] = {arr[start], arr[end], arr[start], arr[end]};
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}


Node getRange(int node, int start, int end, int left, int right) {
    if (right < start or end < left) return tempNode();
    if (left <= start and end <= right) return tree[node];
    Node leftNode = getRange(node*2, start, (start+end)/2, left, right);
    Node rightNode = getRange(node*2+1, (start+end)/2+1, end, left, right);
    return merge(leftNode, rightNode);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }
    init();
    cin >> m;
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        
        if (x2 <= y1) {
            Node leftNode = (x1 <= x2-1) ? getRange(1, 0, n-1, x1, x2-1) : tempNode();
            Node midNode = getRange(1, 0, n-1, x2, y1);
            Node rightNode = (y1+1 <= y2) ? getRange(1, 0, n-1, y1+1, y2) : tempNode();
            ll mx = max({
                leftNode.rmax + midNode.lmax,
                leftNode.rmax + midNode.sum + rightNode.lmax,
                midNode.mmax,
                midNode.rmax + rightNode.lmax
            });
            cout << mx << '\n';
        } else {
            Node leftNode = getRange(1, 0, n-1, x1, y1);
            Node midNode = (y1+1 <= x2-1) ? getRange(1, 0, n-1, y1+1, x2-1) : tempNode();
            Node rightNode = getRange(1, 0, n-1, x2, y2);
            cout << leftNode.rmax + midNode.sum + rightNode.lmax << '\n';
        }
    }


    return 0;
}