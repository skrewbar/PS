#include <bits/stdc++.h>
using namespace std;


int main() {
    string s;
    cin >> s;
    vector<vector<bool>> is_palindrome(s.size(), vector<bool>(s.size()));

    is_palindrome[0][0] = true;
    for (int i = 1; i < s.size(); i++) {
        is_palindrome[i][i] = true;
        if (s[i-1] == s[i]) is_palindrome[i-1][i] = true;
    }

    for (int size = 2; size < s.size(); size++) {
        for (int i = 0; i < s.size() - size; i++) {
            if (s[i] == s[i+size] and is_palindrome[i+1][i+size-1]) is_palindrome[i][i+size] = true;
        }
    }

    vector<int> partition(s.size());
    partition[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        if (is_palindrome[0][i]) {
            partition[i] = 1;
            continue;
        }
        partition[i] = i+1;
        for (int j = 0; j < i; j++) {
            if (is_palindrome[j+1][i]) partition[i] = min(partition[j]+1, partition[i]);
        }
    }
    cout << partition[s.size()-1];
}