#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

string agcu = "^9(u";
int agcuCnt(string s) {
    int ret = 0;

    for (int i = 0; i + 3 < s.size(); i++) {
        if (s.substr(i, 4) == agcu) ret++;
    }

    return ret;
}

map<char, char> rev = {
    {'^', 'v'}, {'v', '^'}, {'9', '6'}, {'6', '9'},
    {'(', ')'}, {')', '('}, {'u', 'n'}, {'n', 'u'},
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string s;
    cin >> s;

    int original = agcuCnt(s);

    for (int i = 0; i < N; i++) s[i] = rev[s[i]];
    reverse(all(s));

    int reversed = agcuCnt(s);

    if (original > reversed) cout << "NO";
    else if (original < reversed) cout << "YES";
    else cout << "SAME";

    return 0;
}