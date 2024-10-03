#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> prop(51);

    for (int i = 0 ; i < n ; i++) {
        int index;
        cin >> index;
        prop[index] += 1;
    }

    int max_val = -1;
    for (int i = 0 ; i < 51 ; i++) {
        if (prop[i] == i) {
            max_val = i;
        }
    }
    
    cout << max_val;

}