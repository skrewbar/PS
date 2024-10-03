#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n; cin >> n;
    vector<int> height(n+2, 0);
    stack<int> s;
    for (int i = 1 ; i <= n ; i++) {
        cin >> height[i];
    }

    int maxS = 0;
    s.push(0);
    for (int i = 1 ; i <= n + 1 ; i++) {
        while (not s.empty() and height[s.top()] > height[i]) {
            int curr = s.top();
            s.pop();
            maxS = max(maxS, height[curr] * (i - 1 - s.top()));
        }
        s.push(i);
    }
    cout << maxS;

    return 0;
}