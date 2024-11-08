#include <bits/stdc++.h>
using namespace std;
using ll = long long;


class segment_tree {
private:
    vector<ll> tree;
    int size;

    void add(int node, int start, int end, int index, ll value) {
        if (index < start or end < index) return;
        if (start == end) {
            tree[node] += value;
            return;
        }
        add(node*2, start, (start+end)/2, index, value);
        add(node*2+1, (start+end)/2+1, end, index, value);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    int get_range_sum(int node, int start, int end, int left, int right) {
        if (right < start or end < left) return 0;
        if (left <= start and end <= right) return tree[node];
        ll lsum = get_range_sum(node*2, start, (start+end)/2, left, right);
        ll rsum = get_range_sum(node*2+1, (start+end)/2+1, end, left, right);
        return lsum + rsum;
    }

public:
    segment_tree(int size) : size(size) {
        int height = ceil(log2(size));
        tree.resize(1 << height + 1);
    }

    void add(int index, ll value) {
        add(1, 0, size-1, index, value);
    }

    int get_range_sum(int left, int right) {
        return get_range_sum(1, 0, size-1, left, right);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pair<int, int>> coords(n);
        for (int i = 0; i < n; i++) {
            cin >> coords[i].first;
            cin >> coords[i].second;
            coords[i].second = -coords[i].second;
        }
        sort(coords.begin(), coords.end());
        vector<int> compressed_y(n);
        for (int i = 0; i < n; i++) {
            compressed_y[i] = coords[i].second;
        }
        sort(compressed_y.begin(), compressed_y.end());
        compressed_y.erase(unique(compressed_y.begin(), compressed_y.end()), compressed_y.end());

        segment_tree tree(compressed_y.size());
        ll answer = 0;
        for (pair<int, int> p : coords) {
            int index = lower_bound(compressed_y.begin(), compressed_y.end(), p.second) - compressed_y.begin();
            answer += tree.get_range_sum(0, index);
            tree.add(index, 1);
        }

        cout << answer << '\n';
    }
}