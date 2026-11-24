#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll merge(vector<ll> &seq, int lo, int hi) {
    ll inversion = 0;
    vector<ll> temp;
    int mid = (lo + hi) / 2;
    int l = lo, r = mid + 1;

    while (l <= mid and r <= hi) {
        if (seq[l] <= seq[r]) temp.push_back(seq[l++]);
        else {
            temp.push_back(seq[r++]);
            inversion += mid - l + 1;
        }
    }
    while (l <= mid) temp.push_back(seq[l++]);
    while (r <= hi) temp.push_back(seq[r++]);
    for (int i = lo; i <= hi; i++) {
        seq[i] = temp[i - lo];
    }
    return inversion;
}


ll count_inversion(vector<ll> &seq, int lo, int hi) {
    ll inversion = 0;
    if (lo < hi) {
        int mid = (lo + hi) / 2;
        inversion += count_inversion(seq, lo, mid);
        inversion += count_inversion(seq, mid+1, hi);
        inversion += merge(seq, lo, hi);
    }
    return inversion;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << count_inversion(arr, 0, arr.size()-1);
}