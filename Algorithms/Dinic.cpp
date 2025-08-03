#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

constexpr int INF = 1e9;

class FlowNetwork {
   public:
    FlowNetwork(size_t size, int source, int sink)
        : source(source), sink(sink), adj(size), curEdge(size), level(size) {}

    void addEdge(int from, int to, int capacity) {
        Edge *edge = new Edge(to, capacity), *rev = new Edge(from, 0);
        edge->rev = rev, rev->rev = edge;
        adj[from].push_back(edge), adj[to].push_back(rev);
    }

    int getMaxFlow() {
        int maxFlow = 0;

        while (buildLevelGraph()) {
            ranges::fill(curEdge, 0);
            int f;
            while ((f = pushFlow(source, INF)))
                maxFlow += f;
        }

        return maxFlow;
    }

   private:
    struct Edge {
        Edge* rev;
        int to, capacity, flow;
        Edge(int to, int capacity) : to(to), capacity(capacity), flow(0) {}

        void pushFlow(int f) {
            flow += f;
            rev->flow -= f;
        }

        int residualCapacity() { return capacity - flow; }
    };

    int source, sink;
    vector<vector<Edge*>> adj;
    vector<int> curEdge, level;

    bool buildLevelGraph() {
        ranges::fill(level, -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);

        while (not q.empty()) {
            int now = q.front();
            q.pop();

            for (Edge* edge : adj[now]) {
                if (level[edge->to] != -1 or edge->residualCapacity() == 0)
                    continue;

                level[edge->to] = level[now] + 1;
                q.push(edge->to);
            }
        }

        return level[sink] != -1;
    }

    int pushFlow(int now, int flow) {
        if (now == sink)
            return flow;

        for (int& i = curEdge[now]; i < (int)adj[now].size(); i++) {
            Edge* edge = adj[now][i];

            if (level[edge->to] != level[now] + 1 or
                edge->residualCapacity() == 0)
                continue;

            int f = pushFlow(edge->to, min(flow, edge->residualCapacity()));
            if (f) {
                edge->pushFlow(f);
                return f;
            }
        }

        return 0;
    }
};