#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll N;
string S;
int cntSum[202020][3];

template <typename T> ll calcSameCount(function<T(int)> func) {
    map<T, int> cnt;
    cnt[func(0)]++;

    ll ret = 0;
    for (int i = 1; i <= N; i++) ret += cnt[func(i)]++;

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    cin >> S;
    S = '#' + S;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 3; j++)
            cntSum[i][j] = cntSum[i - 1][j] + ((S[i] - 'A') == j);
    }

    ll AB =
        calcSameCount<int>([&](int i) { return cntSum[i][0] - cntSum[i][1]; });
    ll BC =
        calcSameCount<int>([&](int i) { return cntSum[i][1] - cntSum[i][2]; });
    ll CA =
        calcSameCount<int>([&](int i) { return cntSum[i][2] - cntSum[i][0]; });
    ll ABC = calcSameCount<pair<int, int>>([&](int i) {
        return pair(cntSum[i][0] - cntSum[i][1], cntSum[i][1] - cntSum[i][2]);
    });

    cout << N * (N + 1) / 2 - (AB + BC + CA - 2 * ABC);

    return 0;
}
