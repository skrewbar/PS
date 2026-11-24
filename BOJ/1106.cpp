#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;
ll maxInt = 2147483647;


struct Information {
    ll cost;
    ll customer;
    Information(ll cost, ll customer) {
        this->cost = cost;
        this->customer = customer;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n;
    cin >> c >> n;
    vector<ll> cost(c+101, maxInt);
    cost[0] = 0;
    vector<Information> informations(n, Information(0, 0));
    for (int i = 0 ; i < n ; i++) {
        cin >> informations[i].cost >> informations[i].customer;
        cost[informations[i].customer] = informations[i].cost;
    }

    for (int customer = 1 ; customer <= c + 100 ; customer++) {
        for (int i = 0 ; i < n ; i++) {
            if (customer < informations[i].customer) {
                continue;
            }
            cost[customer] = min(
                cost[customer],
                cost[customer-informations[i].customer] + informations[i].cost
                );
        }
    }

    ll minCost = maxInt;
    for (int customer = c ; customer <= c + 100 ; customer++) {
        minCost = min(minCost, cost[customer]);
    }

    cout << minCost;
}