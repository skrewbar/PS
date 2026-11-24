#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


int get_flavor(vector<int> &tree, int node, int start, int end, int rank) {
    if (start == end) {
        return start; // 사탕의 맛 리턴
    }
    if (rank <= tree[node*2]) {
        return get_flavor(tree, node*2, start, (start+end)/2, rank);
    } else {
        return get_flavor(tree, node*2+1, (start+end)/2+1, end, rank - tree[node*2]);
    }
}


void update(vector<int> &tree, int node, int start, int end, int index, int val) {
    if (index < start || end < index) {
        return;
    }
    if (start == end) {
        tree[node] += val;
        return;
    }
    update(tree, node*2, start, (start+end)/2, index, val);
    update(tree, node*2+1, (start+end)/2+1, end, index, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}


int main() {
    int flavors = 1000000;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h = (int)ceil(log2(flavors));
    vector<int> tree(1 << (h + 1));

    int n;
    cin >> n;

    while (n--) {
        int a, b, c;
        cin >> a;

        if (a == 1) {
            cin >> b;
            int flavor = get_flavor(tree, 1, 0, flavors-1, b);
            cout << flavor+1 << '\n';
            update(tree, 1, 0, flavors-1, flavor, -1);
        } else {
            cin >> b >> c;
            update(tree, 1, 0, flavors-1, b-1, c);
        }
    }

    return 0;
}