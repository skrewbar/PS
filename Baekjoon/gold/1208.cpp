#include <bits/stdc++.h>
using namespace std;

vector<int> arr;
vector<int> lsum;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, s;
    cin >> n >> s;
    arr.resize(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }


    lsum.resize((1 << n/2));
    for (int include = 0 ; include < (1 << n/2) ; include++) {
        for (int i = 0 ; i < n/2 ; i++) {
            if (include & (1 << i)) {
                lsum[include] += arr[i];
            }
        }
    }
    sort(lsum.begin(), lsum.end());


    long long ans = 0;
    for (int include = 0 ; include < (1 << (n+1)/2) ; include++) {
        int sum = 0;
        for (int i = n/2 ; i < n ; i++) {
            if (include & (1 << (i-n/2))) {
                sum += arr[i];
            }
        }
        
        auto lbound = lower_bound(lsum.begin(), lsum.end(), s-sum);
        auto ubound = upper_bound(lsum.begin(), lsum.end(), s-sum);
        ans += ubound - lbound;
    }
    if (s == 0) ans--;
    cout << ans;
    

    return 0;
}