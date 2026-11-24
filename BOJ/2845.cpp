#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int people, area;
    cin >> people >> area;
    people *= area;
    
    for (int i = 0 ; i < 5 ; i++) {
        int article;
        cin >> article;
        cout << article - people << ' ';
    }
    return 0;
}