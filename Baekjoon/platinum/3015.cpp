#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Person {
    int height, 
    sameHeight; // include itself
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;
    stack<Person> s;
    ll ans = 0;
    for (int i = 0 ; i < n ; i++) {
        int height;
        cin >> height;

        while (not s.empty() and s.top().height < height) {
            ans++;
            s.pop();
        };

        if (not s.empty()) {
            if (s.top().height == height) {
                ans += s.top().sameHeight + (s.top().sameHeight < s.size());
                s.push({height, s.top().sameHeight+1});
            } else {
                ans += 1;
                s.push({height, 1});
            }
        } else s.push({height, 1});
    }

    cout << ans;


    return 0;
}