#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

struct Event {
    int id;
    int p;
    int t;
    bool out;

    bool operator>(const Event &e) const { return t > e.t; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, q;
    cin >> n >> k >> q;

    vector<bool> bringsKey(q);
    vector<Event> events;
    for (int i = 0; i < q; i++) {
        int p, l, r;
        cin >> p >> l >> r;

        events.emplace_back(i, p, l, false);
        events.emplace_back(i, p, r, true);
    }
    sort(all(events), greater<>());

    int homePerson = n;
    int homeKey = k;
    for (auto [id, _, __, out] : events) {
        if (out) {
            if (--homePerson == 0) {
                if (--homeKey < 0) {
                    cout << "impossible";
                    return 0;
                }
                bringsKey[id] = true;
            }
        } else if (not out) {
            homePerson++;
            if (bringsKey[id]) homeKey++;
        }
    }

    for (int i = 0; i < q; i++) cout << bringsKey[i];

    return 0;
}
