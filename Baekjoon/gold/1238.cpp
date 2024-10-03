#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
const int INF = 100001;


vector<int> dijkstra(vector<pair<int, int>> graph[], int start, int studentCount) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heapq;
    heapq.push({0, start});
    vector<int> time(studentCount+1, INF);
    time[start] = 0;

    while (!heapq.empty()) {
        int currentTime = heapq.top().first, currentLoc = heapq.top().second;
        heapq.pop();
        if (time[currentLoc] < currentTime) continue;

        for (pair<int, int> next : graph[currentLoc]) {
            int totalTime = currentTime + next.first;
            if (totalTime < time[next.second]) {
                time[next.second] = totalTime;
                heapq.push({totalTime, next.second});
            }
        }
    }

    return time;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int studentCount, lineCount, partyLocation;
    cin >> studentCount >> lineCount >> partyLocation;
    vector<pair<int, int>> toLine[lineCount+1];
    vector<pair<int, int>> fromLine[lineCount+1];
    for (int i = 0 ; i < lineCount ; i++) {
        int from, to, time;
        cin >> from >> to >> time;
        toLine[from].push_back({time, to});
        fromLine[to].push_back({time, from});
    }

    vector<int> toTime = dijkstra(toLine, partyLocation, studentCount);
    vector<int> fromTime = dijkstra(fromLine, partyLocation, studentCount);
    int maxTime = 0;
    for (int i = 1 ; i <= studentCount ; i++) {
        maxTime = max(maxTime, toTime[i] + fromTime[i]);
    }
    cout << maxTime;


    return 0;
}