#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int X[101], Y[101];
vector<int> elevators[100001];
int previous[101];
bool isEnd[101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        cin >> X[i] >> Y[i];

        for (int floor = X[i]; floor <= N; floor += Y[i])
            elevators[floor].push_back(i);
    }

    int A, B;
    cin >> A >> B;

    for (int i : elevators[B])
        isEnd[i] = true;

    fill(previous + 1, previous + M + 1, -1);

    queue<int> q;
    for (int i : elevators[A]) {
        q.push(i);
        previous[i] = 0;
    }

    int arrival = -1;

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        if (isEnd[now]) {
            arrival = now;
            break;
        }

        for (int f = X[now]; f <= N; f += Y[now]) {
            for (int nxt : elevators[f]) {
                if (previous[nxt] != -1)
                    continue;

                previous[nxt] = now;
                q.push(nxt);
            }
        }
    }

    if (arrival != -1) {
        stack<int> ans;

        while (arrival != 0) {
            ans.push(arrival);
            arrival = previous[arrival];
        }

        cout << ans.size() << '\n';
        while (not ans.empty()) {
            cout << ans.top() << '\n';
            ans.pop();
        }
    } else {
        cout << -1;
    }

    return 0;
}