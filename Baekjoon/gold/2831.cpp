#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> tall_want_men;
    vector<int> small_want_men;
    for (int i = 0; i < n; i++) {
        int height;
        cin >> height;

        if (height < 0) small_want_men.push_back(-height);
        else tall_want_men.push_back(height);
    }

    vector<int> tall_want_women;
    vector<int> small_want_women;
    for (int i = 0; i < n; i++) {
        int height;
        cin >> height;

        if (height < 0) small_want_women.push_back(-height);
        else tall_want_women.push_back(height);
    }

    sort(tall_want_men.begin(), tall_want_men.end());
    sort(small_want_men.begin(), small_want_men.end());
    sort(tall_want_women.begin(), tall_want_women.end());
    sort(small_want_women.begin(), small_want_women.end());

    int answer = 0;
    int i = 0, j = 0;
    while (i < tall_want_men.size() and j < small_want_women.size()) {
        if (tall_want_men[i] < small_want_women[j]) answer++, i++, j++;
        else j++;
    }

    i = 0, j = 0;
    while (i < tall_want_women.size() and j < small_want_men.size()) {
        if (tall_want_women[i] < small_want_men[j]) answer++, i++, j++;
        else j++;
    }

    cout << answer;
}