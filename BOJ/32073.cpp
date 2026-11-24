#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        int firstOne = 0;
        while (firstOne < n and s[firstOne] != '1')
            firstOne++;

        if (firstOne == n) {  // 1이 없다면
            cout << 0 << '\n';
            continue;
        }

        int firstZero = firstOne + 1;
        int oneCount = 1;
        while (firstZero < n and s[firstZero] != '0')
            firstZero++, oneCount++;

        if (firstZero == n) {  // 1이후 0이 등장하지 않는다면
            for (int i = 0; i < s.size() - firstOne - 1; i++)
                cout << 1;
            cout << (firstOne == 0 ? 0 : 1) << '\n';
            continue;
        }

        int secondOne = 1;
        while (secondOne < n and s[firstZero + secondOne] != '1')
            secondOne++;

        int start = firstZero - min(oneCount, secondOne);
        string s2 = s.substr(start, n - firstZero);
        for (int i = 1; i <= s2.size(); i++) {
            s[s.size() - i] =
                (s[s.size() - i] != s2[s2.size() - i] ? '1' : '0');
        }

        for (int i = firstOne; i < n; i++)
            cout << s[i];
        cout << '\n';
    }
}