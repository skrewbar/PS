#include <bits/stdc++.h>
using namespace std;

int fail[1000000];
void setFail(string s) {
    for (int i = 1, j = 0; i < s.length(); i++) {
        while(j > 0 and s[i] != s[j]) j = fail[j-1];
        if (s[i] == s[j]) fail[i] = ++j;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string t, p;
    cin >> t >> p;
    
    for (int i = 0, j = 0; i < t.size(); i++) {
        while (j > 0 and t[i] != p[j]) j = fail[j-1];

        if (t[i] == p[j]) {
            if (j == p.size() - 1) {
                // 찾음
                j = fail[j];
            } else j++;
        }
    }

    return 0;
}