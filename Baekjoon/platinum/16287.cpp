#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int w, n;
    cin >> w >> n;

    vector<int> parcels(n);
    for (int i = 0; i < n; i++) cin >> parcels[i];

    vector<pair<int, int>> twoSum(w, pair{-1, -1});
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int weight = parcels[i] + parcels[j];
            if (weight >= twoSum.size()) continue;
            twoSum[weight] = pair{i, j};
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int weight = w - (parcels[i] + parcels[j]);
            if (weight >= twoSum.size()) continue;
            auto [first, second] = twoSum[weight];
            if (first == -1) continue;
            if (first == i or first == j or second == i or second == j) continue;
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
}