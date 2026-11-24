#include <bits/stdc++.h>
using namespace std;

int n;
int arr[1000];
int DP[1000];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
        DP[i] = arr[i];
    }

    for (int i = 1 ; i < n ; i++) {
        for (int j = 0 ; j < i ; j++) {
            if (arr[j] < arr[i]) DP[i] = max(DP[i], DP[j] + arr[i]);
        }
    }

    cout << *max_element(DP, DP+1000);


    return 0;
}