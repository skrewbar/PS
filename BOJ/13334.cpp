#include <bits/stdc++.h>
using namespace std;

class CommuteLine {
public:
    int left, right;

    CommuteLine(int home, int office) {
        left = home, right = office;
        if (right < left) swap(left, right);
    }

    bool operator<(const CommuteLine &l) {
        if (right != l.right) return right < l.right;
        return left < l.left;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<CommuteLine> lines;
    lines.reserve(n);
    for (int i = 0; i < n; i++) {
        int h, o;
        cin >> h >> o;
        lines.emplace_back(h, o);
    }
    sort(lines.begin(), lines.end());

    int d;
    cin >> d;

    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto [left, right] : lines) {
        pq.push(left);
        while (not pq.empty() and right - pq.top() > d) pq.pop();
        ans = max((int)pq.size(), ans);
    }
    cout << ans;
}