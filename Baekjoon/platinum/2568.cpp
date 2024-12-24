#include <bits/stdc++.h>
#define a first
#define b second
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int wire_count;
    cin >> wire_count;

    vector<pair<int, int>> wire(wire_count);
    for (int i = 0; i < wire_count; i++) {
        int a_wire, b_wire;
        cin >> a_wire >> b_wire;
        wire[i] = {a_wire, b_wire};
    }
    sort(wire.begin(), wire.end());

    vector<int> lis;
    vector<int> lis_index(wire_count);
    for (int i = 0; i < wire_count; i++) {
        int index = lower_bound(lis.begin(), lis.end(), wire[i].b) - lis.begin();
        lis_index[i] = index;
        if (index == lis.size()) lis.push_back(wire[i].b);
        else lis[index] = wire[i].b;
    }
    cout << wire_count - lis.size() << '\n';

    stack<int> rev_lis;
    int finding_index = lis.size()-1;
    for (int i = wire_count-1; i >= 0; i--) {
        if (lis_index[i] == finding_index) {
            rev_lis.push(i);
            finding_index--;
        }
        if (finding_index < 0) break;
    }

    for (int i = 0; i < wire_count; i++) {
        if (not rev_lis.empty() and rev_lis.top() == i) rev_lis.pop();
        else cout << wire[i].a << '\n';
    }
}