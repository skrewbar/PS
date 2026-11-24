#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<bool> matched;
vector<int> matching;
vector<vector<int>> works;

// 매칭에 성공하면 true
bool match(int p) {
    for (int work : works[p]) {
        if (matched[work])
            continue;
        matched[work] = true;

        if (matching[work] == -1 or match(matching[work])) {
            matching[work] = p;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    matched = vector(m, false);
    matching = vector(m, -1);
    works = vector(n, vector<int>());

    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        while (c--) {
            int work;
            cin >> work;
            work--;
            ASSERT(0 <= work and work < m);
            works[i].push_back(work);
        }
    }

    int matchingCnt = 0;
    for (int i = 0; i < n; i++) {
        ranges::fill(matched, false);
        if (match(i))
            matchingCnt++;
    }

    for (int i = 0; i < n and k > 0; i++) {
        ranges::fill(matched, false);
        if (match(i)) {
            k--;
            matchingCnt++;
        }
    }

    cout << matchingCnt;
}