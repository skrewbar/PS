#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MIN_DEFAULT = 11;
constexpr ll MAX_DEFAULT = 0;
constexpr ll ADD_DEFAULT = 0;

struct Node {
    ll minimum, maximum, sum;
    ll minlazy, maxlazy, addlazy;
    int count[11];

    Node() : minimum(LLONG_MAX), maximum(LLONG_MIN), sum(0), minlazy(MIN_DEFAULT), maxlazy(MAX_DEFAULT), addlazy(ADD_DEFAULT) {
        fill(count, count+11, 0);
    }
    Node(ll m, ll M, ll s) : minimum(m), maximum(M), sum(s), minlazy(MIN_DEFAULT), maxlazy(MAX_DEFAULT), addlazy(ADD_DEFAULT) {
        fill(count, count+11, 0);
    }

    void min_range(ll m) {
        minlazy = min(m - addlazy, minlazy);
        maxlazy = min(m - addlazy, maxlazy);
    }

    void max_range(ll M) {
        minlazy = max(M - addlazy, minlazy);
        maxlazy = max(M - addlazy, maxlazy);
    }

    void add_range(ll a) {
        addlazy += a;
    }

    void update(int start, int end) {
        if (minlazy != MIN_DEFAULT) {
            if (minlazy < 0) { // addlazy가 10을 넘긴 경우
                int value = max(minlazy, maxlazy) + addlazy;

                fill(count, count+11, 0);
                if (value <= 10) count[value] = end - start + 1;

                minimum = value, maximum = value;
                sum = value * (end - start + 1);

                minlazy = MIN_DEFAULT, maxlazy = MAX_DEFAULT, addlazy = ADD_DEFAULT;
            } else {
                int over_count = (end - start + 1);
                sum = 0;

                for (int i = 0; i <= minlazy; i++) {
                    over_count -= count[i];
                    sum += count[i] * i;
                }

                sum += over_count * minlazy;
                count[minlazy] += over_count;
                fill(count+minlazy+1, count+11, 0);

                minimum = min(minlazy, minimum);
                maximum = min(minlazy, maximum);

                minlazy = MIN_DEFAULT;
            }
        }

        if (maxlazy <= 0) maxlazy = MAX_DEFAULT; // maxlazy < 0 이면 적용 후에 바뀌는게 없으므로 적용 x
        if (maxlazy != MAX_DEFAULT) {
            for (int i = 0; i < maxlazy; i++) {
                sum += (maxlazy - i) * count[i];
                count[maxlazy] += count[i];
                count[i] = 0;
            }

            minimum = max(maxlazy, minimum);
            maximum = max(maxlazy, maximum);

            maxlazy = MAX_DEFAULT;
        }

        if (addlazy != ADD_DEFAULT) {
            for (int i = 10-addlazy; i >= 1; i--) {
                count[i+addlazy] += count[i];
                count[i] = 0;
            }

            sum += addlazy * (end - start + 1);
            minimum += addlazy;
            maximum += addlazy;

            addlazy = ADD_DEFAULT;
        }
    }
};
vector<Node> tree;
vector<ll> arr;

void merge(Node &parent, Node u, Node v) {
    parent.minimum = min(u.minimum, v.minimum);
    parent.maximum = max(u.maximum, v.maximum);
    parent.sum = u.sum + v.sum;

    parent.minlazy = MIN_DEFAULT;
    parent.maxlazy = MAX_DEFAULT;
    parent.addlazy = ADD_DEFAULT;

    fill(parent.count, parent.count+11, 0);
    for (int i = 1; i <= 10; i++) {
        parent.count[i] = u.count[i] + v.count[i];
    }
}

void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = Node(arr[start], arr[start], arr[start]);
        if (arr[start] <= 10) tree[node].count[arr[start]]++;
    } else {
        int mid = (start + end) / 2;
        init(node<<1, start, mid);
        init(node<<1|1, mid+1, end);
        merge(tree[node], tree[node<<1], tree[node<<1|1]);
    }
}

void propagate(int node, int start, int end) {
    if (start != end) {
        if (tree[node].minlazy != MIN_DEFAULT) {
            tree[node<<1].min_range(tree[node].minlazy);
            tree[node<<1|1].min_range(tree[node].minlazy);
        }

        if (tree[node].maxlazy != MAX_DEFAULT) {
            tree[node<<1].max_range(tree[node].maxlazy);
            tree[node<<1|1].max_range(tree[node].maxlazy);
        }

        if (tree[node].addlazy != ADD_DEFAULT) {
            tree[node<<1].add_range(tree[node].addlazy);
            tree[node<<1|1].add_range(tree[node].addlazy);
        }
    }

    tree[node].update(start, end);
}

void update_range(int node, int start, int end, int left, int right, int value, int query) {
    if (right < start or end < left) return;
    propagate(node, start, end);
    if (left <= start and end <= right) {
        if (query == 1) tree[node].min_range(value);
        else if (query == 2) tree[node].max_range(value);
        else tree[node].add_range(value);
        propagate(node, start, end);
    } else {
        int mid = (start + end) / 2;
        update_range(node<<1, start, mid, left, right, value, query);
        update_range(node<<1|1, mid+1, end, left, right, value, query);
        merge(tree[node], tree[node<<1], tree[node<<1|1]);
    }
}


Node query_range(int node, int start, int end, int left, int right) {
    if (right < start or end < left) return Node();
    propagate(node, start, end);
    if (left <= start and end <= right) {
        return tree[node];
    } else {
        int mid = (start + end) / 2;
        Node l = query_range(node<<1, start, mid, left, right);
        Node r = query_range(node<<1|1, mid+1, end, left, right);
        Node ret;
        merge(ret, l, r);
        return ret;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    tree.resize(1 << 1 + (int)ceil(log2(n)));
    init(1, 0, n-1);

    int m;
    cin >> m;
    while (m--) {
        int q, l, r;
        cin >> q >> l >> r;
        l--;
        r--;

        if (q <= 3) {
            int x;
            cin >> x;
            update_range(1, 0, n-1, l, r, x, q);
        } else {
            Node ans = query_range(1, 0, n-1, l, r);
            // if (q == 4) cout << ans.minimum;
            // else if (q == 5) cout << ans.maximum;
            // else cout << ans.sum;
            cout << ans.minimum << ' ' << ans.maximum << ' ' << ans.sum;
            cout << '\n';
        }
    }
}