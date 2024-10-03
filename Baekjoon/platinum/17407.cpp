#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> tree;
vector<int> arr;

void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = {arr[start], arr[start]};
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = {
            tree[node*2].first + tree[node*2+1].first,
            min(
                tree[node*2].second,
                tree[node*2].first + tree[node*2+1].second
            )
        };
    }
}

void update(int node, int start, int end, int index, int value) {
    if (index < start or end < index) return;
    if (start == end) {
        tree[node] = {value, value};
        return;
    }
    update(node*2, start, (start+end)/2, index, value);
    update(node*2+1, (start+end)/2+1, end, index, value);
    tree[node] = {
        tree[node*2].first + tree[node*2+1].first,
        min(
            tree[node*2].second,
            tree[node*2].first + tree[node*2+1].second
        )
    };
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    string s; cin >> s;
    int n = s.size();
    arr.resize(n);
    for (int i = 0 ; i < n ; i++) {
        if (s[i] == '(') arr[i] = 1;
        else arr[i] = -1;
    }

    int height = (int)ceil(log2(n));
    tree.resize(1 << (height + 1));
    init(1, 0, n-1);

    int m; cin >> m;
    int ans = 0;
    while (m--) {
        int index; cin >> index;
        index--;

        arr[index] *= -1;
        update(1, 0, n-1, index, arr[index]);

        if (tree[1].first == 0 and tree[1].second >= 0) ans++;
    }
    cout << ans;


    return 0;
}