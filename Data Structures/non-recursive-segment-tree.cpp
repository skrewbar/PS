#include <bits/stdc++.h>
using namespace std;
using ll = long long;


class segment_tree {
private:
    vector<ll> t;
    int size;
public:
    segment_tree(vector<ll> arr) : size(arr.size()) {
        t.resize(size*2);

        for (int i = 0; i < size; i++) {
            t[i + size] = arr[i];
        }

        for (int node = size-1; node > 0; node--) {
            t[node] = t[node << 1] + t[node << 1 | 1];
        }
    }

    void set(int index, ll value) {
        for (t[index += size] = value; index > 1; index >>= 1) {
            t[index >> 1] = t[index] + t[index ^ 1];
        }
    }

    ll get_range_sum(int left, int right) {
        ll sum = 0;
        for (left += size, right += size; left <= right; left >>= 1, right >>= 1) {
            if (left & 1) sum += t[left++];
            if (~right & 1) sum += t[right--];
        }
        return sum;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    segment_tree tree(arr);

    int q = m + k;
    while (q--) {
        ll a, b, c;
        cin >> a >> b >> c;
        
        if (a == 1) {
            tree.set(b-1, c);
        } else {
            cout << tree.get_range_sum(b-1, c-1) << '\n';
        }
    }
}