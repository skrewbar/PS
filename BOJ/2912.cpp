#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

mt19937 urng(random_device{}());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;

    vector<int> hatColor(n);
    vector<vector<int>> colorIndices(c+1);
    for (int i = 0; i < n; i++) {
        cin >> hatColor[i];
        colorIndices[hatColor[i]].push_back(i);
    }

    int m;
    cin >> m;
    while (m--) {
        int a, b, answer = -1;
        cin >> a >> b;
        a--, b--;

        uniform_int_distribution<int> gen(a, b);
        for (int i = 0; i < 50; i++) {
            int color = hatColor[gen(urng)];
            int cnt = upper_bound(colorIndices[color].begin(),
                                  colorIndices[color].end(), b) -
                      lower_bound(colorIndices[color].begin(),
                                  colorIndices[color].end(), a);
            if (cnt > (b - a + 1) / 2) {
                answer = color;
                break;
            }
        }

        if (answer != -1)
            print("yes {}\n", answer);
        else
            print("no\n");
    }
}