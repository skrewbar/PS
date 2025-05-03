#include <bits/stdc++.h>
using namespace std;

using ll = long long;


class compare {
public:
    bool operator()(const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
        return p1.second > p2.second;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n;
    cin >> c >> n;

    vector<ll> t(c);
    for (int i = 0; i < c; i++) cin >> t[i];
    
    vector<pair<ll, ll>> cow(n);
    for (int i = 0; i < n; i++) cin >> cow[i].first >> cow[i].second;

    sort(t.begin(), t.end());
    sort(cow.begin(), cow.end(), greater<>());

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, compare> pq;

    int answer = 0;
    for (int i = 0; i < c; i++) {
        while (not cow.empty() and cow.back().first <= t[i]) {
            pq.push(cow.back());
            cow.pop_back();
        }
        if (pq.empty()) continue;

        pair<ll, ll> matching = pq.top();
        pq.pop();
        while (not pq.empty() and matching.second < t[i]) {
            matching = pq.top();
            pq.pop();
        }

        if (t[i] <= matching.second) {
            answer++;

            // cout << t[i] << ' ' << matching.first << ' ' << matching.second << '\n';
        }
    }

    cout << answer;
}