#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<vector<int>> dp, mentees;
vector<int> skill;

void setupDp(int i) {
    for (int child : mentees[i]) {
        setupDp(child);
        dp[i][0] += max(dp[child][0], dp[child][1]);
    }

    for (int child : mentees[i]) {
        int mChild = max(dp[child][0], dp[child][1]);
        dp[i][1] = max(dp[i][1], dp[i][0] - mChild + dp[child][0] +
                                     skill[i] * skill[child]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    dp = vector(n + 1, vector(2, 0));
    mentees = vector(n + 1, vector<int>());
    skill = vector<int>(n + 1);

    for (int i = 2; i <= n; i++) {
        int mentor;
        cin >> mentor;
        mentees[mentor].push_back(i);
    }

    for (int i = 1; i <= n; i++)
        cin >> skill[i];

    setupDp(1);
    print("{}", max(dp[1][0], dp[1][1]));

    return 0;
}