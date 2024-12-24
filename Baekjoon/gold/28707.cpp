#include <bits/stdc++.h>
using namespace std;

template <typename T>
using greater_priority_queue = priority_queue<T, vector<T>, greater<T>>;

class Operation {
public:
    int left, right, cost;
    Operation() = default;
    Operation(int left, int right, int cost) : left(left), right(right), cost(cost) {}
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &i : arr) cin >> i;

    int m;
    cin >> m;
    vector<Operation> operations(m);
    for (auto &[l, r, c] : operations) {
        cin >> l >> r >> c;
        l--, r--;
    }
    
    map<vector<int>, int> cost;
    cost[arr] = 0;
    greater_priority_queue<pair<int, vector<int>>> pq;
    pq.push({0, arr});
    while (not pq.empty()) {
        auto [cur_cost, cur] = pq.top();
        pq.pop();

        if (cost.find(cur) != cost.end() and cost[cur] < cur_cost) continue;

        for (auto [l, r, c] : operations) {
            swap(cur[l], cur[r]);
            if (cost.find(cur) == cost.end()) {
                cost[cur] = cur_cost + c;
                pq.push({cost[cur], cur});
            }
            else if (cur_cost + c < cost[cur]) {
                cost[cur] = cur_cost + c;
                pq.push({cost[cur], cur});
            }
            swap(cur[l], cur[r]);
        }
    }

    sort(arr.begin(), arr.end());

    cout << (cost.find(arr) != cost.end() ? cost[arr] : -1);
}