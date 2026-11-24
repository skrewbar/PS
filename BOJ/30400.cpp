#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> manacher(const string& s) {
    vector<int> radius(s.size());

    int r = 0;
    int c = 0;

    for (int i = 0; i < s.size(); i++) {
        if (i <= r)
            radius[i] = min(r - i, radius[2 * c - i]);

        while (i - radius[i] - 1 >= 0 and i + radius[i] + 1 < s.size() and
               s[i - radius[i] - 1] == s[i + radius[i] + 1])
            radius[i]++;

        if (i + radius[i] >= r) {
            r = i + radius[i];
            c = i;
        }
    }

    return radius;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    string word;
    cin >> word;

    string extended = "#";
    extended.reserve(N << 1 | 1);
    for (int i = 0; i < N; i++) {
        extended.push_back(word[i]);
        extended.push_back('#');
    }

    int ans = 0;
    vector<int> radius = manacher(extended);
    for (int i = 0; i < extended.size(); i++) {
        if (radius[i] >= M) {
            ans++;

            if ((M & 1) != (radius[i] & 1))
                i += (M << 1);
            else
                i += (M << 1) - 1;
        }
    }

    cout << ans;

    return 0;
}