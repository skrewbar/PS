#include <iostream>
#include <queue>
using namespace std;

queue<int> q;
int time[200001];


bool isValid(int index) {
    if (0 <= index and index < 200001 and time[index] == 0) {
        return true;
    }
    return false;
}


int getMinTime(int pos, int destination) {
    q.push(pos);
    while (not q.empty()) {
        int now = q.front();
        q.pop();

        if (now == destination) {
            return time[now];
        }
        if (isValid(now+1)) {
            q.push(now+1);
            time[now+1] = time[now] + 1;
        }
        if (isValid(now-1)) {
            q.push(now-1);
            time[now-1] = time[now] + 1;
        }
        if (isValid(now*2)) {
            q.push(now*2);
            time[now*2] = time[now] + 1;
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; cin >> n >> k;
    cout << getMinTime(n, k);

    return 0;
}