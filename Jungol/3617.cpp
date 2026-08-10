#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

using ll = long long;

struct Company {
    ll price, day;

    bool operator<(const Company &c) const {
        return tie(day, price) < tie(c.day, c.price);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<Company> manufac(m);
    for (int i = 0; i < m; i++) {
        auto &[p, d] = manufac[i];
        cin >> p >> d;
    }
    sort(all(manufac));
    vector<Company> temp;
    temp.push_back(manufac.front());
    for (auto [p, d] : manufac)
        if (temp.back().price > p) temp.emplace_back(p, d);
    manufac = std::move(temp);

    vector<Company> consume(n);
    for (int i = 0; i < n; i++) {
        auto &[q, e] = consume[i];
        cin >> q >> e;
    }
    sort(all(consume));
    reverse(all(consume));
    temp.clear();
    temp.push_back(consume.front());
    for (auto [p, d] : consume)
        if (temp.back().price < p) temp.emplace_back(p, d);
    consume = std::move(temp);
    reverse(all(consume));

    m = manufac.size();
    n = consume.size();

    ll ans = 0;

    auto dnc = [&](auto self, int s, int e, int l, int r) -> void {
        if (s > e) return;

        int mid = (s + e) / 2;
        auto [sell, start] = manufac[mid];

        ll res = LLONG_MIN;
        int opt = l;
        while (opt <= r and consume[opt].day < start) opt++;
        for (int i = opt; i <= r; i++) {
            auto [buy, end] = consume[i];

            if (maximize(res, (end - start) * (buy - sell))) opt = i;
        }
        if (opt > r) opt = r;

        maximize(ans, res);

        self(self, s, mid - 1, l, opt);
        self(self, mid + 1, e, opt, r);
    };

    dnc(dnc, 0, m - 1, 0, n - 1);

    cout << ans;

    return 0;
}
