#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
    int n, s; cin >> n >> s;
    vector<int> arr(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }

    int left = 0;
    int right = 0;
    int minLen = 1000001;
    int sum = arr[0];
    while (left <= right and right < n) {
        if (sum < s) {
            right++;
            sum += arr[right];
        } else {
            minLen = min(minLen, right - left + 1);
            sum -= arr[left];
            left++;
        }
    }
    if (minLen == 1000001) cout << 0;
    else cout << minLen;


    return 0;
}