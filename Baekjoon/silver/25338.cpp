#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d, n;
    cin >> a >> b >> c >> d >> n;

    auto f = [a, b, c, d](int x) { return max(a * (x - b) * (x - b) + c, d); };

    int answer = 0;
    while (n--) {
        int u, v;
        cin >> u >> v;
        if (u == f(v)) answer++;
    }

    cout << answer;
}