#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }

template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

struct Art {
    ll size, value;
};

Art arts[505050];
ll valueSum[505050];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> arts[i].size >> arts[i].value;
    sort(arts + 1, arts + N + 1, by(size));

    for (int i = 1; i <= N; i++)
        valueSum[i] = valueSum[i - 1] + arts[i].value;

    ll answer = 0;
    ll m = 0;
    for (int i = 1; i <= N; i++) {
        maximize(m, arts[i].size - valueSum[i - 1]);
        maximize(answer, m + valueSum[i] - arts[i].size);
    }

    cout << answer;

    return 0;
}