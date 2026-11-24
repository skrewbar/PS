#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<MinHeap<int>> restQueue(n + 1);
    set<pair<int, int>> restCount;  // (count, dish)
    set<pair<int, int>> minRest;    // (restaurant, dish)
    for (int i = 1; i <= n; i++) {
        int dish;
        cin >> dish;
        restQueue[dish].emplace(i);
        if ((int)restQueue[dish].size() > (n + 1) / 2) {
            cout << -1;
            return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (not restQueue[i].empty()) {
            restCount.emplace(restQueue[i].size(), i);
            minRest.emplace(restQueue[i].top(), i);
        }
    }

    for (int lastDish = -1, remainRest = n; remainRest > 0; remainRest--) {
        int dish;
        auto [maxCount, maxDish] = *restCount.rbegin();

        if (maxCount > remainRest / 2)
            dish = maxDish;
        else {
            auto iter = minRest.begin();
            ASSERT(iter->second != lastDish or
                   next(iter, 1)->second != lastDish);
            dish = (iter->second == lastDish ? (next(iter, 1))->second
                                             : iter->second);
        }
        lastDish = dish;

        int rest = restQueue[dish].top();
        int count = restQueue[dish].size();
        cout << rest << ' ';
        restQueue[dish].pop();

        restCount.erase(pair(count, dish));
        minRest.erase(pair(rest, dish));

        if (--count > 0) {
            restCount.emplace(count, dish);
            minRest.emplace(restQueue[dish].top(), dish);
        }
    }

    return 0;
}