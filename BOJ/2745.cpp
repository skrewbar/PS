#include <iostream>
#include <map>
#include <cmath>
using namespace std;
map<char, int> arith_table;

void setup() {
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0 ; i < 36 ; i++) {
        arith_table.insert({alphabet[i], i});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setup();
    
    string n;
    int b;
    cin >> n >> b;
    
    int answer = 0;
    int len = n.length() - 1;
    for (int i = 0 ; i < len+1 ; i++) {
        answer += arith_table[n[len - i]] * (pow(b, i));
    }
    cout << answer;
}