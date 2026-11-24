#include <bits/stdc++.h>
using namespace std;

int n;
struct Node {
    int max, min;
};

vector<Node> tree;


Node merge(Node n1, Node n2) {
    return {max(n1.max, n2.max), min(n1.min, n2.min)};
}


void init(int node = 1, int start = 0, int end = n-1) {
    if (start == end) {
        tree[node] = {start, end};
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}


void change(int node, int start, int end, int index, int value) {
    if (index < start or end < index) return;
    if (start == end) {
        tree[node] = {value, value};
        return;
    }
    change(node*2, start, (start+end)/2, index, value);
    change(node*2+1, (start+end)/2+1, end, index, value);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}


Node getRange(int node, int start, int end, int left, int right) {
    if (right < start or end < left) return {0, n+1};
    if (left <= start and end <= right) return tree[node];

    Node left_node = getRange(node*2, start, (start+end)/2, left, right);
    Node right_node = getRange(node*2+1, (start+end)/2+1, end, left, right);
    return merge(left_node, right_node);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> n >> k;
        int height = (int) ceil(log2(n));
        tree.resize(1 << (height + 1));
        init();

        while (k--) {
            int q, a, b;
            cin >> q >> a >> b;

            if (q == 0) {
                Node a_node = getRange(1, 0, n-1, a, a);
                Node b_node = getRange(1, 0, n-1, b, b);

                change(1, 0, n-1, a, b_node.max);
                change(1, 0, n-1, b, a_node.max);
            } else {
                Node node = getRange(1, 0, n-1, a, b);
                if (node.min == a and node.max == b) cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }


    return 0;
}