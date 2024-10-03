#include <bits/stdc++.h>
using namespace std;

int n;
int lis[1000000];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    int lisSize = 0;
    for (int i = 0 ; i < n ; i++) {
        int element;
        cin >> element;
        int index = lower_bound(lis, lis+lisSize, element) - lis;

        if (index == lisSize) {
            lis[lisSize] = element;
            lisSize++;
        } else {
            lis[index] = element;
        }
    }

    cout << lisSize;


    return 0;
}