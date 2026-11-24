#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;
vector<int> DP;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    arr.resize(n);
    DP.resize(n, 0);
    for (int i = 0 ; i < n ; i++) cin >> arr[i];

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < i ; j++) {
            if (arr[i] > arr[j]) DP[i] = max(DP[i], DP[j] + 1);
        }
    }

    int lisLen = *max_element(DP.begin(), DP.end()) + 1;
    cout << lisLen << '\n';
    stack<int> s;
    int findingIndex = lisLen - 1;

    for (int i = n-1 ; 0 <= i ; i--) {
        if (DP[i] == findingIndex) {
            s.push(arr[i]);
            findingIndex--;
        }
        if (findingIndex == -1) break;
    }

    while (not s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }


    return 0;
}