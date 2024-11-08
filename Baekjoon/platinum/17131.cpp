#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
constexpr ll COORD_MAX = 2e5;


class segment_tree {
private:
    vector<ll> t;
    int n;
public:
    segment_tree(int n) : n(n) {
        t.resize(n*2);
    }

    void add(int i) { for (t[i+=n]++ ; i > 1; i >>= 1) t[i>>1] = (t[i] + t[i^1]) % MOD; }
    ll get_range_sum(int l, int r) {
        ll sum = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l&1) sum += t[l++];
            if (~r&1) sum += t[r--];
            sum %= MOD;
        }
        return sum;
    }
};


bool compare(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> stars(n);
    for (int i = 0; i < n; i++) {
        cin >> stars[i].first;
        cin >> stars[i].second;
        stars[i].first += COORD_MAX;
        stars[i].second += COORD_MAX;
    }
    sort(stars.begin(), stars.end(), compare);

    segment_tree tree(COORD_MAX*2+1);
    queue<pair<int, int>> q;
    ll answer = 0;
    for (pair<int, int> star : stars) {
        if (not q.empty() and q.back().second != star.second) {
            while (not q.empty()) {
                pair<int, int> now = q.front(); q.pop();
                tree.add(now.first);
            }
        }

        answer += tree.get_range_sum(0, star.first-1) % MOD * tree.get_range_sum(star.first+1, COORD_MAX*2) % MOD;
        answer %= MOD;

        q.push(star);

        // cout << tree.get_range_sum(0, star.first-1) << ' ' << tree.get_range_sum(star.first+1, COORD_MAX*2) << '\n';
    }

    cout << answer;
}