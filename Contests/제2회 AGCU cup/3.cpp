#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string s;
    if (N & 1) s.push_back('A');
    if (N & 1 << 1) s.push_back('G');
    if (N & 1 << 2) s.push_back('C');
    if (N & 1 << 3) s.push_back('U');

    while (s.size() < 4) s.push_back(s.back());

    cout << s;

    return 0;
}