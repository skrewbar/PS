#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<string, greater<string>> attending;

    while (n--) {
        string name, log;
        cin >> name >> log;

        if (log == "enter") attending.insert(name);
        else attending.erase(name);
    }

    for (string name : attending) cout << name << '\n';
}