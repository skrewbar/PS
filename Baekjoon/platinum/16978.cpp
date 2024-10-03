#include<bits/stdc++.h>
using namespace std;
using ll = long long;


int n;
vector<ll> arr;
vector<ll> tree;
vector<pair<int, pair<int, ll>>> changeQueries;
vector<vector<int>> sumQueries;
vector<ll> answer;


void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}


void updateTree(int node, int start, int end, int index, int value) {
    if (index < start or end < index) {
        return;
    }
    if (start == end) {
        tree[node] = value;
        return;
    }
    updateTree(node*2, start, (start+end)/2, index, value);
    updateTree(node*2+1, (start+end)/2+1, end, index, value);
    tree[node] = tree[node*2] + tree[node*2+1];
}


ll getRangeSum(int node, int start, int end, int left, int right) {
    if (right < start or end < left) {
        return 0;
    }
    if (left <= start and end <= right) {
        return tree[node];
    }
    ll lsum = getRangeSum(node*2, start, (start+end)/2, left, right);
    ll rsum = getRangeSum(node*2+1, (start+end)/2+1, end, left, right);
    return lsum + rsum;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    arr = vector<ll>(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }
    int height = (int)ceil(log2(n));
    tree = vector<ll>(1 << (height + 1));
    init(1, 0, n-1);

    int m; cin >> m;
    int i = 1;
    int j = 0;
    while (m--) {
        int qType;
        cin >> qType;
        
        if (qType == 1) {
            int index, value;
            cin >> index >> value;
            changeQueries.push_back({i, {index-1, value}});
            i++;
        } else {
            int number, left, right;
            cin >> number >> left >> right;
            sumQueries.push_back({number, left-1, right-1, j});
            j++;
        }
    }
    answer = vector<ll>(j);

    sort(changeQueries.begin(), changeQueries.end());
    sort(sumQueries.begin(), sumQueries.end());
    
    i = 0;
    for (vector<int> sumQuery : sumQueries) {
        int number = sumQuery[0], left = sumQuery[1], right = sumQuery[2], j = sumQuery[3];
        while (i < changeQueries.size() and changeQueries[i].first <= sumQuery[0]) {
            int index = changeQueries[i].second.first;
            int value = changeQueries[i].second.second;
            updateTree(1, 0, n-1, index, value);
            i++;
        }
        answer[j] = getRangeSum(1, 0, n-1, left, right);
    }

    for (int i = 0 ; i < j ; i++) {
        cout << answer[i] << '\n';
    }
    return 0;
}