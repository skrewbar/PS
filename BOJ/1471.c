#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MX 202020

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int next[MX];

typedef struct {
    int u, v;
} Edge;
Edge edges[MX];
int st[MX], ed[MX];
int ascEdge(const void *a, const void *b) {
    Edge x = *(const Edge *)a;
    Edge y = *(const Edge *)b;

    if (x.u < y.u) return -1;
    if (x.u > y.u) return 1;

    if (x.v < y.v) return -1;
    if (x.v > y.v) return 1;

    return 0;
}

int depth[MX];
int queue[MX];
int front = 0, back = 0;

int order[MX];
int counter = 0;

int stack[MX];
int top = 0;

int scc[MX];
int sccSz[MX];
int sccId = 0;

int topoSorted[MX];
int topoEnd = 0;

int findSCC(int cur) {
    order[cur] = counter++;
    stack[top++] = cur;

    int lowLink = order[cur];

    int nxt = next[cur];

    if (scc[nxt] == -1) {
        if (order[nxt] == -1) {
            int nxtLink = findSCC(nxt);
            lowLink = MIN(lowLink, nxtLink);
        } else lowLink = MIN(lowLink, order[nxt]);
    }

    if (lowLink == order[cur]) {
        while (1) {
            int t = stack[--top];

            topoSorted[topoEnd++] = t;
            scc[t] = sccId;
            sccSz[sccId]++;

            if (t == cur) break;
        }
        sccId++;
    }

    return lowLink;
}

int digitSum(int x) {
    int ret = 0;

    while (x > 0) {
        ret += x % 10;
        x /= 10;
    }

    return ret;
}

int main() {
    int N;
    scanf("%d", &N);

    memset(order, -1, sizeof(int) * (N + 1));
    memset(scc, -1, sizeof(int) * (N + 1));

    for (int i = 1; i <= N; i++) {
        next[i] = (i + digitSum(i) - 1) % N + 1;

        Edge e = {next[i], i};
        edges[i - 1] = e;
    }

    qsort(edges, N, sizeof(Edge), ascEdge);
    memset(ed, -1, sizeof(int) * (N + 1));
    st[edges[0].u] = 0;
    for (int i = 1; i < N; i++) {
        if (edges[i - 1].u != edges[i].u) {
            st[edges[i].u] = i;
            ed[edges[i - 1].u] = i - 1;
        }
    }
    ed[edges[N - 1].u] = N - 1;

    for (int i = 1; i <= N; i++)
        if (order[i] == -1) findSCC(i);

    int ans = 0;
    memset(depth, -1, sizeof(int) * (N + 1));
    for (int sIndex = 0; sIndex < N; sIndex++) {
        int start = topoSorted[sIndex];

        if (depth[start] != -1 || scc[start] == -1) continue;

        front = back = 0;
        queue[back++] = start;
        depth[start] = 0;

        int maxDepth = 0;

        while (back - front) {
            int u = queue[front++];
            maxDepth = MAX(maxDepth, depth[u]);

            for (int i = st[u]; i <= ed[u]; i++) {
                int v = edges[i].v;

                if (depth[v] != -1) continue;

                if (scc[v] != scc[start]) depth[v] = depth[u] + 1;
                else depth[v] = 0;

                queue[back++] = v;
            }
        }

        ans = MAX(ans, sccSz[scc[start]] + maxDepth);
    }

    printf("%d", ans);

    return 0;
}
