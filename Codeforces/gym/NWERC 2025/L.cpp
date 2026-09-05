#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_set<string> names;
    unordered_map<string, vector<int>> mp;
    unordered_map<string, int> total;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            string name;
            cin >> name;

            names.insert(name);

            if (not mp.contains(name)) {
                mp[name] = vector<int>(10);
                total[name] = 0;
            }

            mp[name][j]++;
            total[name]++;
        }
    }

    auto comp = [&](string a, string b) {
        if (total[a] != total[b]) return total[a] < total[b];

        for (int i = 0; i < 10; i++)
            if (mp[a][i] != mp[b][i]) return mp[a][i] < mp[b][i];

        return false;
    };

    string ans = *names.begin();
    for (string name : names) {
        if (comp(ans, name))
            ans = name;
    }

    for (string name : names) {
        if (name == ans) continue;

        if (not comp(ans, name) and not comp(name, ans)) {
            cout << "tie";
            return 0;
        }
    }

    cout << ans;

    return 0;
}
