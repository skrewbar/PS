#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


struct Node {
    int num;
    int dist;
};

int v, maxDist, maxNum;
bool visited[100001];
vector<Node> graph[100001];

void dfs(Node node) {
    int num = node.num;
    int dist = node.dist;

    if (visited[num]) return;
    if (maxDist < dist) {
        maxDist = dist;
        maxNum = num;
    }
    visited[num] = true;

    for (int i = 0 ; i < graph[num].size() ; i++) {
        Node nxtNode = graph[num][i];
        nxtNode.dist += dist;
        dfs(nxtNode);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> v;
    int from, to, dist;
    for (int i = 0 ; i < v ; i++) {
        cin >> from;
        while (true) {
            cin >> to;
            if (to == -1) break;
            cin >> dist;
            graph[from].push_back({to, dist});
            graph[to].push_back({from, dist});
        }
    }

    dfs({1, 0});
    memset(visited, false, sizeof(visited));
    maxDist = 0;
    dfs({maxNum, 0});

    cout << maxDist;

    return 0;
}