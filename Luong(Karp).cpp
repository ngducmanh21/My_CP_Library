// Karp
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct canh
{
    int u, v;
    int c;
    int f;
};

struct mang 
{
    int n;
    int source, sink;

    vector<vector<int> > a;
    vector<canh> E;

    vector<int> cur;
    vector<int> dist;

    mang() {}
    mang(int n, int s, int t) 
	{
        this->n = n;
        source = s; sink = t;
        a = vector<vector<int> > (n + 1);
        cur = dist = vector<int> (n + 1);
    }

    void themcanh(int u, int v, int c) 
	{
        a[u].push_back(E.size()); E.push_back({u, v, c, 0});
        a[v].push_back(E.size()); E.push_back({v, u, 0, 0});
    }

    bool bfs() 
	{
        fill(dist.begin(), dist.end(), -1);
        queue<int> Q; Q.push(source); dist[source] = 0;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int i = 0; i < (int) a[u].size(); ++i) {
                int id = a[u][i], v = E[id].v;
                if (dist[v] < 0 && E[id].f < E[id].c) {
                    dist[v] =  dist[u] + 1;
                    Q.push(v);
                }
            }
        }
        return dist[sink] >= 0;
    }

    int dfs(int u, int f) 
	{
        if (!f) return 0;
        if (u == sink) return f;
        for (; cur[u] < (int) a[u].size(); ++cur[u]) {
            int id = a[u][cur[u]], v = E[id].v;
            if (dist[v] != dist[u] + 1) continue;
            int delta = dfs(v, min(f, E[id].c - E[id].f));
            if (delta) {
                E[id].f += delta; E[id ^ 1].f -= delta;
                return delta;
            }
        }
        return 0;
    }

    int maxf() 
	{
        int ans = 0;
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            while (true) {
                int delta = dfs(source, INF);
                if (!delta) break;
                ans += delta;
            }
        }
        return ans;
    }
};

int main() 
{
    ios::sync_with_stdio(false);
    freopen("TASK.inp", "r", stdin);
    freopen("TASK.out", "w", stdout);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    mang G (n, s, t);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        G.themcanh(u, v, c);
    }
    cout << G.maxf() << endl;
    return 0;
}
