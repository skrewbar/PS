#include <bits/stdc++.h>
using namespace std;

vector<int> prime_numbers;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    // 에라토스테네스의 체체체
    for (int i = 2 ; i < 1000 ; i++) {
        bool is_prime = true;
        for (int prime_number : prime_numbers) {
            if (i % prime_number == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) prime_numbers.push_back(i);
    }
    

    int t;
    cin >> t;
    while (t--) {
        int num;
        cin >> num;

        bool is_find = false;
        for (int i : prime_numbers) {
            if (is_find) break;
            for (int j : prime_numbers) {
                if (is_find) break;
                for (int k : prime_numbers) {
                    if (i + j + k == num) {
                        cout << i << ' ' << j << ' ' << k << '\n';
                        is_find = true;
                        break;
                    }
                }
            }
        }
    }


    return 0;
}