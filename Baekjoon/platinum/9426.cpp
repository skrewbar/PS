#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int temps[250001];
const int maxTemp = 65535;


struct SegmentTree {
    int tree[300000];
    
    SegmentTree() {
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


    int find(int node, int start, int end, int num) {
        if (start == end) return start;
        if (num <= tree[node*2]) {
            return find(node*2, start, (start+end)/2, num);
        } else {
            return find(node*2+1, (start+end)/2+1, end, num - tree[node*2]);
        }
    }
} segmentTree;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, k;
    ll ans = 0;
    cin >> n >> k;
    

    for (int i = 1 ; i <= n ; i++) {
        cin >> temps[i];
    }
    temps[0] = -1;

    for (int i = 1 ; i < k ; i++) {
        segmentTree.add(1, 0, maxTemp, temps[i], 1);
    }
    int startIndex = 0;
    for (int i = k ; i <= n ; i++) {
        segmentTree.add(1, 0, maxTemp, temps[i], 1);
        segmentTree.add(1, 0, maxTemp, temps[startIndex++], -1);
        ans += segmentTree.find(1, 0, maxTemp, (k+1)/2);
    }

    cout << ans;

    return 0;
}