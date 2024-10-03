#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool can = true;
    int n;
    cin >> n;
    char first;
    string word;
    cin >> word;
    first = word.front();
    
    for (int i = 0 ; i < n-1 ; i++) {
        cin >> word;
        if (first != word.front()) {
            can = false;
            break;
        }
    }

    if (can) {
        cout << 1;
    } else {
        cout << 0;
    }
}