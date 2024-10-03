#include <iostream>
using namespace std;
using ll = long long;

int mu[44722];


void setup() {
    mu[1] = 1; // 뫼비우스 함숫값 전처리
    for (int i = 1 ; i <= 44721 ; i++) {
        for (int j = 2 * i ; j <= 44721 ; j += i) {
            mu[j] -= mu[i];
        }
    }
}

ll get_SFI_count(ll k) { // k까지의 제곱ㄴㄴ수의 개수
    ll count = 0;
    for (ll i = 1 ; i * i <= k; i++) {
        count += mu[i] * (k / (i * i));
    }
    return count;
}

int get_SFI(int search, ll start, ll end) {
    ll mid = (start+end)/2;
    ll sfi_count = get_SFI_count(mid);
    

    if (sfi_count == search) {
        mid--;
        while (get_SFI_count(mid) == search) {
            mid--;
        }
        return mid+1;
    }
    else if (sfi_count > search) return get_SFI(search, start, mid-1);
    else return get_SFI(search, mid+1, end);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setup();


    ll k;
    cin >> k;

    cout << get_SFI(k, k, k*2);

    return 0;
}