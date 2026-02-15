#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> length(N + 2);  // the length of the squares
    for (int i = 1; i <= N; i++)
        cin >> length[i];

    vector<ll> rightEnd(length);  // the rightmost position of the squares
    for (int i = 2; i <= N + 1; i++)
        rightEnd[i] += rightEnd[i - 1];

    stack<int> stk;
    stk.push(0);

    ll ans = length[0] * length[0];
    pair<int, int> ansPair{1, 1};

    for (int i = 1; i <= N + 1; i++) {
        while (length[stk.top()] > length[i]) {
            int top = stk.top();
            stk.pop();

            ll score =
                ((rightEnd[i] - length[i]) - rightEnd[stk.top()]) * length[top];
            if (score > ans) {
                ans = score;
                ansPair = {stk.top() + 1, i - 1};
            }
        }

        stk.push(i);
    }

    println("{}", ans);
    println("{} {}", ansPair.first, ansPair.second);

    return 0;
}