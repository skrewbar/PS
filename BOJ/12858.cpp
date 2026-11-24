#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;


ll gcd(ll a, ll b) {
    ll r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}


void gcd_init(vector<ll> &tree, vector<ll> &seq, int node, int start, int end) {
    if (start == end) {
        if (start == 0) {
            tree[node] = seq[0];
        } else {
            tree[node] = abs(seq[start] - seq[start-1]); //리프 노드에는 왼쪽 수와의 차 저장
        }
    } else {
        gcd_init(tree, seq, node*2, start, (start+end)/2);
        gcd_init(tree, seq, node*2+1, (start+end)/2+1, end);
        tree[node] = gcd(tree[node*2], tree[node*2+1]);
    }
}


void gcd_update(vector<ll> &tree, int node, int start, int end, int index, int value) {
    if (index < start || end < index) {
        return;
    }
    if (start == end) {
        tree[node] = value;
        return;
    }
    gcd_update(tree, node*2, start, (start+end)/2, index, value);
    gcd_update(tree, node*2+1, (start+end)/2+1, end, index, value);
    tree[node] = gcd(tree[node*2], tree[node*2+1]);
}


ll get_range_gcd(vector<ll> &tree, int node, int start, int end, int left, int right) {
    if (right < start || end < left) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    ll lgcd = get_range_gcd(tree, node*2, start, (start+end)/2, left, right);
    ll rgcd = get_range_gcd(tree, node*2+1, (start+end)/2+1, end, left, right);
    return gcd(lgcd, rgcd);
}



void lazy_init(vector<ll> &tree, vector<ll> &seq, int node, int start, int end) {
    if (start == end) {
        tree[node] = seq[start];
    } else {
        lazy_init(tree, seq, node*2, start, (start+end)/2);
        lazy_init(tree, seq, node*2+1, (start+end)/2+1, end);
    }
}


void lazy_add_range(vector<ll> &tree, int node, int start, int end, int left, int right, int value) {
    if (right < start || end < left) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += value;
        return;
    }
    lazy_add_range(tree, node*2, start, (start+end)/2, left, right, value);
    lazy_add_range(tree, node*2+1, (start+end)/2+1, end, left, right, value);
}


ll get_by_index(vector<ll> &tree, int node, int start, int end, int index) {
    if (index < start || end < index) {
        return 0;
    }
    if (start == end) {
        return tree[node];
    }
    ll lval = get_by_index(tree, node*2, start, (start+end)/2, index);
    ll rval = get_by_index(tree, node*2+1, (start+end)/2+1, end, index);
    return lval + rval + tree[node];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;

    vector<ll> seq(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> seq[i];
    }

    int h = (int)ceil(log2(n));
    int tree_size = (1 << (h+1));
    vector<ll> gcd_tree(tree_size);
    vector<ll> lazy_tree(tree_size);

    gcd_init(gcd_tree, seq, 1, 0, n-1);
    lazy_init(lazy_tree, seq, 1, 0, n-1);
    cin >> m;
    while (m--) {
        ll t;
        int left, right;
        cin >> t >> left >> right;
        left--;right--;
        if (t == 0) {
            if (left == right) {
                cout << get_by_index(lazy_tree, 1, 0, n-1, left) << '\n';
            } else {
                cout << gcd(get_by_index(lazy_tree, 1, 0, n-1, left), get_range_gcd(gcd_tree, 1, 0, n-1, left+1, right)) << '\n';
            }
        } else {
            lazy_add_range(lazy_tree, 1, 0, n-1, left, right, t);
            if (left != 0) {
                ll difference = abs(get_by_index(lazy_tree, 1, 0, n-1, left) - get_by_index(lazy_tree, 1, 0, n-1, left-1));
                gcd_update(gcd_tree, 1, 0, n-1, left, difference);
            } 
            if (right+1 < n) {
                ll difference = abs(get_by_index(lazy_tree, 1, 0, n-1, right+1) - get_by_index(lazy_tree, 1, 0, n-1, right));
                gcd_update(gcd_tree, 1, 0, n-1, right+1, difference);
            }
        }
    }
}