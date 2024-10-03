#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> array(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> array[i];
    }

    int v, count;
    cin >> v;
    count = 0;
    for (int i = 0 ; i < n ; i++) {
        if (array[i] == v) {
            count += 1;
        }
    }
    cout << count;

    return 0;
}