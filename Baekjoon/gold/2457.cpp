#include <bits/stdc++.h>
using namespace std;

class Date {
public:
    int month, day;

    Date() {}
    Date(int month, int day) : month(month), day(day) {}
    
    bool operator==(const Date &d) const {
        return month == d.month and day == d.day;
    }

    bool operator!=(const Date &d) const {
        return not (*this == d);
    }

    bool operator<(const Date &d) const {
        if (month != d.month) return month < d.month;
        return day < d.day;
    }

    bool operator<=(const Date &d) const {
        return (*this < d) or (*this == d);
    }
};

class Flower {
public:
    Date bloom, fall;

    bool operator<(const Flower &f) const {
        if (bloom != f.bloom) return bloom < f.bloom;
        return fall < f.fall;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Flower> flowers;
    flowers.reserve(n);
    for (int i = 0; i < n; i++) {
        Flower f;
        cin >> f.bloom.month >> f.bloom.day >> f.fall.month >> f.fall.day;
        flowers.push_back(f);
    }

    sort(flowers.begin(), flowers.end());

    if (Date(3, 1) < flowers[0].bloom) {
        cout << 0;
        return 0;
    }

    int ans = 0;
    Date last_fall(3, 1);
    const Date end(11, 30);
    
    int i = 0;
    while (i < n) {
        if (end < last_fall) break;
        if (last_fall < flowers[i].bloom) break;

        Date temp_last_fall = last_fall;
        while (i < n) {
            if (last_fall < flowers[i].bloom) break;
            temp_last_fall = max(flowers[i].fall, temp_last_fall);
            i++;
        }
        last_fall = temp_last_fall;
        ans++;
    }

    cout << (end < last_fall ? ans : 0);
}