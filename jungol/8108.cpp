#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define by(x) [](const auto &a, const auto &b) { return a.x < b.x; }

constexpr int INF = 1e9;

struct Fish {
    int sz, color;
} fish[505050];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        char color;
        cin >> fish[i].sz >> color;

        if (color == 'R') fish[i].color = 0;
        else if (color == 'G') fish[i].color = 1;
        else fish[i].color = 2;
    }
    sort(fish + 1, fish + N + 1, by(sz));

    vector<tuple<int, int, int>> cuboids;
    int cnt[3] = {};
    for (int i = 1, j = 1; j <= N; j++) {
        cnt[fish[j].color]++;

        while (fish[i].sz * 2 <= fish[j].sz) cnt[fish[i++].color]--;

        cuboids.emplace_back(cnt[0] + 1, cnt[1] + 1, cnt[2] + 1);
    }

    sort(all(cuboids),
         [](const auto &a, const auto &b) { return get<2>(a) > get<2>(b); });
    cuboids.emplace_back(0, 0, 0);

    ll volume = 0;
    ll area = 0;
    set<pair<int, int>> points = {
        {0, INF},
        {INF, 0},
    };

    for (int i = 0; i < (int)cuboids.size() - 1; i++) {
        auto [r, g, b] = cuboids[i];

        auto addArea = [&]() {
            volume += area * (get<2>(cuboids[i]) - get<2>(cuboids[i + 1]));
        };

        auto it = points.lower_bound({r, g});
        if (g <= it->second) {
            addArea();
            continue;
        }

        ll baseG = it->second;
        --it;

        vector<pair<int, int>> rmList;

        while (it->second <= g) {
            auto left = it;
            --left;

            area -= (it->first - left->first) * (it->second - baseG);

            rmList.push_back(*it);

            --it;
            if (it == points.begin()) break;
        }

        for (auto p : rmList) points.erase(p);
        points.emplace(r, g);

        area += (r - it->first) * (g - baseG);

        addArea();
    }

    cout << volume - 1;

    return 0;
}
