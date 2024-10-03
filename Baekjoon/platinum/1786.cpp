#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}


vector<int> getFail(string str) {
    vector<int> fail(str.length());

    for (int i = 1, j = 0; i < str.length(); i++) {
        while (j > 0 and str[i] != str[j]) j = fail[j-1];
        if (str[i] == str[j]) fail[i] = ++j;
    }

    return fail;
}


int main() {
    fastio();

    string t, p;
    getline(cin, t);
    getline(cin, p);
    vector<int> fail = getFail(p);
    vector<int> answers;

    for (int i = 0, j = 0; i < t.size(); i++) {
        while (j > 0 and t[i] != p[j]) j = fail[j-1];

        if (t[i] == p[j]) {
            if (j == p.size() - 1) {
                answers.push_back(i + 1 - (p.size() - 1));
                j = fail[j];
            } else j++;
        }
    }

    cout << answers.size() << '\n';
    for (int i : answers) {
        cout << i << ' ';
    }

    return 0;
}