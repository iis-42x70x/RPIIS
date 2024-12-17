#include <iostream>
#include <vector>

using namespace std;


struct Edge {
    int v;
    int flow;
    int capacity;

    Edge(int v, int capacity)
    : v(v), flow(0), capacity(capacity) {}

    int get_capacity() {
        return capacity - flow;
    }
};

const int INF = (int)(1e9) + 666;
const int N = 666;
int used[N];
int timer = 1;


vector<Edge> edges;
vector<int> graph[N];

void add_edge(int v, int u, int capacity) {
    graph[v].emplace_back(edges.size());
    edges.emplace_back(u, capacity);
    graph[u].emplace_back(edges.size());
    edges.emplace_back(v, 0);
}


int dfs(int v, int min_capacity, int t) {
    if (v == t) {
        return min_capacity;
    }
    used[v] = timer;
    for (int index : graph[v]) {
        if (edges[index].get_capacity() == 0) {
            continue;
        }
        if (used[edges[index].v] == timer) {
            continue;
        }
        int x = dfs(edges[index].v, min(min_capacity, edges[index].get_capacity()), t);
        if (x) {
            edges[index].flow += x;
            edges[index ^ 1].flow -= x;
            return x;
        }
    }
    return 0;
}

int get_flow(int s, int t){
    for(int i = 0; i < edges.size(); i++){
        edges[i].flow = 0;
    }
    timer = 1;
    for(int i = 0; i < N; i++)
        used[i] = 0;
    while (dfs(s, INF, t)) {
        ++timer;
    }
    int result = 0;
    for (int index : graph[s]) {
        result += edges[index].flow;
    }
    return result;
}


int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        add_edge(v, u, 1);
        add_edge(u,v, 1);
    }
    int ans = INF;
    for(int s = 1; s <= n; s++){
        for(int t = s + 1; t <= n; t++){
            int flow = get_flow(s, t);
            ans = min(ans, flow);
        }
    }
    cout << ans;
}