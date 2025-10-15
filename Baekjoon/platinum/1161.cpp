#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct Group {
    int S, E, M;

    bool operator<(const Group& g) { return S < g.S; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N, C;
    cin >> K >> N >> C;

    vector<Group> groups(K);
    for (int i = 0; i < K; i++)
        cin >> groups[i].S >> groups[i].E >> groups[i].M;
    sort(groups.begin(), groups.end());

    int ans = 0;
    multiset<int> getOn;
    for (auto [S, E, M] : groups) {
        while (not getOn.empty() and *getOn.begin() <= S)
            getOn.erase(getOn.begin());

        while (M > 0 and getOn.size() < C) {
            getOn.insert(E);
            ans++;
            M--;
        }

        while (M > 0 and not getOn.empty() and *getOn.rbegin() > E) {
            getOn.erase(--getOn.end());
            getOn.insert(E);
            M--;
        }
    }

    cout << ans;

    return 0;
}