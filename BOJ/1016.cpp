#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll minLimit, maxLimit;
    cin >> minLimit >> maxLimit;

    vector<bool> b제곱ㄴㄴ(maxLimit - minLimit + 1, true);

    for (ll i = 2; i * i <= maxLimit; i++) {
        for (ll j = minLimit / (i*i) * i*i; j <= maxLimit; j += i*i) {
            if (j < minLimit) continue;
            b제곱ㄴㄴ[j - minLimit] = false;
        }
    }

    int answer = 0;
    for (int i = 0; i < maxLimit - minLimit + 1; i++) {
        if (b제곱ㄴㄴ[i]) answer++;
    }
    cout << answer;
}