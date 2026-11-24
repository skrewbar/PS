#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> houses;
    vector<pair<int, int>> chicken_stores;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int room;
            cin >> room;

            if (room == 1) houses.push_back({i, j});
            if (room == 2) chicken_stores.push_back({i, j});
        }
    }

    int min_city_chicken_dist = INT_MAX;
    for (int k = 1; k < 1 << chicken_stores.size(); k++) {
        int chicken_count = 0;
        for (int i = 0; i < chicken_stores.size(); i++) {
            if (k & 1 << i) chicken_count++;
        }
        if (chicken_count > m) continue;

        vector<pair<int, int>> available_chicken;
        for (int i = 0; i < chicken_stores.size(); i++) {
            if (k & 1 << i) available_chicken.push_back(chicken_stores[i]);
        }

        int city_chicken_dist = 0;
        for (auto house : houses) {
            int chicken_dist = INT_MAX;
            for (auto chick : available_chicken) {
                chicken_dist = min(abs(chick.first - house.first) + abs(chick.second - house.second), chicken_dist);
            }
            city_chicken_dist += chicken_dist;
        }
        min_city_chicken_dist = min(city_chicken_dist, min_city_chicken_dist);
    }
    cout << min_city_chicken_dist;

    return 0;
}