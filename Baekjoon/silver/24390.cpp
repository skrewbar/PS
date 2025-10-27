#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string time;
    cin >> time;

    int i = 0;
    int minute = 0;
    while (time[i] != ':') {
        minute *= 10;
        minute += time[i] - '0';
        i++;
    }

    i++;
    int second = 0;
    while (i < time.size()) {
        second *= 10;
        second += time[i] - '0';
        i++;
    }

    second += minute * 60;

    int ans = 1;

    while (second >= 600) {
        second -= 600;
        ans++;
    }
    while (second >= 60) {
        second -= 60;
        ans++;
    }
    if (second >= 30)
        second -= 30;
    while (second >= 30) {
        second -= 30;
        ans++;
    }
    while (second >= 10) {
        second -= 10;
        ans++;
    }

    cout << ans;

    return 0;
}