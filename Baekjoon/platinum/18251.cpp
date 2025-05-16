#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll MIN = -1e9;

struct Node {
    int y;
    ll w;

    bool operator<=>(const Node& n) const = default;
};

vector<int> weight;
vector<Node> points;
int n;

void setup(int node, int depth) {
    if (node > n)
        return;

    setup(node << 1, depth + 1);
    points.emplace_back(depth, weight[node]);
    setup(node << 1 | 1, depth + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    weight = vector<int>(n+1);
    for (int i = 1; i <= n; i++)
        cin >> weight[i];

    points.reserve(n);
    setup(1, 0);

    int height = 32 - __builtin_clz(n + 1) + 1;
    ll answer = MIN;
    for (int lo = 0; lo < height; lo++) {
        for (int hi = lo; hi < height; hi++) {
            ll sum = 0;
            for (int i = 0; i < n; i++) {
                if (points[i].y < lo or hi < points[i].y)
                    continue;
                answer = max(answer, sum + points[i].w);

                sum += points[i].w;
                if (sum < 0)
                    sum = 0;
            }
        }
    }

    cout << answer;
}