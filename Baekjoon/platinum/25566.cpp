#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;


class Ingredient {
public:
    int l, r, v;

    bool operator<(const Ingredient &ingred) {
        if (l != ingred.l) return l < ingred.l;
        return r > ingred.r;
    }
};


bool compare(const Ingredient &i1, const Ingredient &i2) {
    return i1.r < i2.r;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Ingredient> ingredients(n);
    for (auto &[l, r, v] : ingredients) {
        cin >> l >> r >> v;
    }
    sort(ingredients.begin(), ingredients.end());

    vector<Ingredient> kim(n + 1);
    vector<long long> answer(n + 1);
    int kimCount = 0;
    int maxRight = -2e9;
    for (int i = 0; i < n; i++) {
        auto [l, r, v] = ingredients[i];
        if (r > maxRight) {
            maxRight = r;
            kim[kimCount++] = ingredients[i];
            continue;
        }

        int bound = lower_bound(kim.begin(), kim.begin() + kimCount, ingredients[i], compare) - kim.begin();
        answer[bound] += v;
        answer[kimCount] -= v;
    }

    for (int i = 0; i < n; i++) answer[i + 1] += answer[i];
    for (int i = 0; i < kimCount; i++) {
        answer[i] += kim[i].v;
    }

    cout << *max_element(answer.begin(), answer.end());
}