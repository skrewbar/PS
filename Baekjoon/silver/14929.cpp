#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> x(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    vector<ll> prefixSum(x);
    for (int i = 0; i + 1 < n; i++)
        prefixSum[i + 1] += prefixSum[i];

    ll answer = 0;
    for (int i = 1; i < n; i++)
        answer += x[i] * prefixSum[i - 1];

    cout << answer;
}