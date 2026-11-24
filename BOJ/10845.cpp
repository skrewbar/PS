#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    queue<int> q;

    for (int i = 0 ; i < n ; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "push") {
            int x;
            cin >> x;
            q.push(x);
        } else if (cmd == "pop") {
            if (q.empty()) cout << -1 << '\n';
            else {
                cout << q.front() << '\n';
                q.pop();
            }
        } else if (cmd == "size") {
            cout << q.size() << '\n';
        } else if (cmd == "empty") {
            if (q.empty()) cout << 1 << '\n';
            else cout << 0 << '\n';
        } else if (cmd == "front") {
            if (q.empty()) cout << -1 << '\n';
            else cout << q.front() << '\n';
        } else if (cmd == "back") {
            if (q.empty()) cout << -1 << '\n';
            else cout << q.back() << '\n';
        }
    }
}