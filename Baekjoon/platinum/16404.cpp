#include <bits/stdc++.h>
using namespace std;

int tree[400001];
int visit_order[100001];
int max_child[100001];
vector<int> childs[100001];
int order = 0;


void ett(int x) {
    visit_order[x] = ++order;
    
    for (int child : childs[x]) ett(child);

    max_child[x] = order;
}


void addRange(int node, int start, int end, int left, int right, int value) {
    if (right < start or end < left) return;
    if (left <= start and end <= right) {
        tree[node] += value;
        return;
    }

    addRange(node*2, start, (start+end)/2, left, right, value);
    addRange(node*2+1, (start+end)/2+1, end, left, right, value);
}


int get(int node, int start, int end, int index) {
    if (index < start or end < index) return 0;
    if (start == end) return tree[node];
    int left = get(node*2, start, (start+end)/2, index);
    int right = get(node*2+1, (start+end)/2+1, end, index);
    return left + right + tree[node];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;

    int parent;
    cin >> parent;
    for (int i = 2 ; i <= n ; i++) {
        cin >> parent;
        childs[parent].push_back(i);
    }

    ett(1);

    
    while (m--) {
        int cmd, i;
        cin >> cmd >> i;

        if (cmd == 1) {
            int w;
            cin >> w;
            addRange(1, 1, order, visit_order[i], max_child[i], w);
        } else {
            cout << get(1, 1, order, visit_order[i]) << '\n';
        }
    }


    return 0;
}