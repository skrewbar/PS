#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<ll> arr(n);

        for (int i = 0 ; i < n ; i++) {
            cin >> arr[i];
        }

        sort(arr.begin(), arr.end());

        ll minDist = LLONG_MAX;
        int count = 0;


        int left = 0, right = n - 1;
        while (left < right) {
            if (abs(arr[left] + arr[right] - k) == minDist) {
                count++;
            } else if (abs(arr[left] + arr[right] - k) < minDist) {
                minDist = abs(arr[left] + arr[right] - k);
                count = 1;
            }

            if (arr[left] + arr[right] <= k) {
                left++;
            } else {
                right--;
            }
        }

        cout << count << '\n';
    }


    return 0;
}