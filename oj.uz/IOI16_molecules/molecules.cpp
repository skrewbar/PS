#include "molecules.h"
#include <algorithm>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }

struct Molecule {
    ll w;
    int idx;
};

vector<int> find_subset(int l, int u, vector<int> w) {
    int n = w.size();

    vector<Molecule> molecules(n);
    for (int i = 0; i < n; i++)
        molecules[i] = {w[i], i};

    sort(all(molecules), by(w));

    ll sum = 0;
    int hi = 0;
    while (hi < n and sum < l)
        sum += molecules[hi++].w;
    hi--;

    if (sum < l)
        return {};

    if (sum <= u) {
        vector<int> ret;
        for (int i = 0; i <= hi; i++)
            ret.push_back(molecules[i].idx);
        return ret;
    }

    sum -= molecules[0].w;
    int lo = 1;
    while (hi + 1 < n and sum < l)
        sum += molecules[++hi].w - molecules[lo++].w;

    if (l <= sum) {
        vector<int> ret;
        for (int i = lo; i <= hi; i++)
            ret.push_back(molecules[i].idx);
        return ret;
    }

    return {};
}
