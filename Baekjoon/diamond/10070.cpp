#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

const int INF = 100000;


class Node {
public:
    int maxLazy, minLazy;

    Node() {
        maxLazy = 0;
        minLazy = 0;
    }
};


class Wall {
private:
    vector<Node> tree;
    int wallSize;

    void update(int node, int query, int value) {
        if (query == 1) {
            tree[node].maxLazy = max(tree[node].maxLazy, value);
            tree[node].minLazy = max(tree[node].minLazy, value);
        } else {
            tree[node].maxLazy = min(tree[node].maxLazy, value);
            tree[node].minLazy = min(tree[node].minLazy, value);
        }
    }


    void propagate(int node, int start, int end) {
        if (start != end) {
            update(node*2, 1, tree[node].maxLazy);
            update(node*2, 2, tree[node].minLazy);
            update(node*2+1, 1, tree[node].maxLazy);
            update(node*2+1, 2, tree[node].minLazy);

            tree[node].maxLazy = 0;
            tree[node].minLazy = INF;
        }
    }


    void rangeUpdate(int node, int start, int end, int left, int right, int query, int value) {
        propagate(node, start, end);
        if (right < start or end < left) return;
        if (left <= start and end <= right) {
            update(node, query, value);
            return;
        }
        rangeUpdate(node*2, start, (start+end)/2, left, right, query, value);
        rangeUpdate(node*2+1, (start+end)/2+1, end, left, right, query, value);
    }


    int getValue(int node, int start, int end, int index) {
        propagate(node, start, end);
        if (start == end) return tree[node].maxLazy;
        if (index <= (start+end)/2) {
            return getValue(node*2, start, (start+end)/2, index);
        } else {
            return getValue(node*2+1, (start+end)/2+1, end, index);
        }
    }
    
public:
    Wall(int wallSize) : wallSize(wallSize) {
        int height = (int) ceil(log2(wallSize));
        tree.resize(1 << (height + 1), Node());
    }

    void buildWall(int left, int right, int op, int height) {
        rangeUpdate(1, 0, wallSize-1, left, right, op, height);
    }

    int getWallHeight(int pos) {
        return getValue(1, 0, wallSize-1, pos);
    }
};


int main() {
    fastio();

    int n, k;
    cin >> n >> k;

    Wall wall(n);

    while (k--) {
        int op, left, right, height;
        cin >> op >> left >> right >> height;

        wall.buildWall(left, right, op, height);
    }

    for (int i = 0; i < n; i++) {
        cout << wall.getWallHeight(i) << '\n';
    }

    return 0;
}