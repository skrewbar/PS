#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Query {
    ll x, l, r, v;

    constexpr bool operator<(const Query &q) const {
        if (x != q.x) return x < q.x;
        if (l != q.l) return l < q.l;
        if (r != q.r) return r < q.r;
        return v <= q.v;
    }
};

vector<ll> tree;
vector<ll> cnt;
vector<ll> unique_y;
vector<Query> queries;

void add_range(int node, int start, int end, int left, int right, int value) {
    if (right < start or end < left) return;
    if (left <= start and end <= right) {
        cnt[node] += value;
    } else {
        int mid = (start + end) / 2;
        add_range(node<<1, start, mid, left, right, value);
        add_range(node<<1|1, mid+1, end, left, right, value);
    }

    if (cnt[node]) tree[node] = unique_y[end+1] - unique_y[start];
    else {
        if (start == end) tree[node] = 0;
        else tree[node] = tree[node<<1] + tree[node<<1|1];
    }
}


void process_query(Query q) {
    int l = lower_bound(unique_y.begin(), unique_y.end(), q.l) - unique_y.begin();
    int r = lower_bound(unique_y.begin(), unique_y.end(), q.r) - unique_y.begin();
    add_range(1, 0, unique_y.size()-1, l, r-1, q.v);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        queries.push_back({x1, y1, y2, 1});
        queries.push_back({x2, y1, y2, -1});

        unique_y.push_back(y1);
        unique_y.push_back(y2);
    }

    sort(unique_y.begin(), unique_y.end());
    unique_y.erase(unique(unique_y.begin(), unique_y.end()), unique_y.end());

    tree.resize(unique_y.size() * 4);
    cnt.resize(unique_y.size() * 4);

    sort(queries.begin(), queries.end());
    process_query(queries[0]);

    ll ans = 0;
    for (int i = 1; i < static_cast<int>(queries.size()); i++) {
        ans += (queries[i].x - queries[i-1].x) * tree[1];
        process_query(queries[i]);
    }

    cout << ans;
}