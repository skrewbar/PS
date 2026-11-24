#include <iostream>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s)) {
        string wrong = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;\'ZXCVBNM,./";
        map<char, char> cor_table;

        cor_table.insert({' ', ' '});
        for (int i = 1 ; i < wrong.length() ; i++) {
            cor_table.insert({wrong[i], wrong[i-1]});
        }

        for (int i = 0 ; i < s.length() ; i++) {
            char letter = s[i];
            cout << cor_table[letter];
        }
        cout << '\n';
    }
}