#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<int, string, greater<>> textByTime;
    textByTime.insert({0, ""});

    string text;
    int n;
    cin >> n;
    while (n--) {
        string cmdType;
        cin >> cmdType;

        if (cmdType == "type") {
            string value;
            int time;
            cin >> value >> time;
            text += value;
            textByTime.insert({time, text});
        } else {
            int undoTime, time;
            cin >> undoTime >> time;
            auto iter = textByTime.upper_bound(time - undoTime);
            text = iter == textByTime.end() ? "" : iter->second;
            textByTime.insert({time, text});
        }
    }

    cout << text;
}