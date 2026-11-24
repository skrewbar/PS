#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> pos(n);
    for (int i = 0; i < n; i++)
        cin >> pos[i];

    vector<ll> popTime(n);
    for (int i = 0; i < n; i++)
        cin >> popTime[i];

    ll time, truckPos;
    time = truckPos = pos.back();
    for (int i = n-1; i >= 0; i--) {
        time = max(time + truckPos - pos[i], popTime[i]);
        truckPos = pos[i];
    }
    time += truckPos;

    cout << time;
}