#include <bits/stdc++.h>
using namespace std;

int atk[2000];
int lds[2000];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0 ; i < n ; i++) {
        cin >> atk[i];
    }

    fill(lds, lds+2000, 1);
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < i ; j++) {
            if (atk[j] > atk[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }

    cout << n - *max_element(lds, lds+2000);


    return 0;
}