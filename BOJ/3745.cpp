#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    while (cin >> n) {
        vector<int> lis;
        while (n--) {
            int element;
            cin >> element;

            int index = lower_bound(lis.begin(), lis.end(), element) - lis.begin();

            if (index == lis.end() - lis.begin()) lis.push_back(element);
            else lis[index] = element;
        }
        cout << lis.size() << '\n';
    }


    return 0;
}