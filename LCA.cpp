// Euler Tour
int n, query, m, p[2*N][20], times, L[N], R[N], dist[N], LG2[N];
vector <int> adj[N];
int Log2(int x){
    int k = 1, cnt = 0;
    while (k*2 <= x) k *= 2, cnt++;
    return cnt;
}
void dfs(int u, int par = -1){
    L[u] = R[u] = ++times;
    p[times][0] = u;
    for (auto v:adj[u]){
        if (v == par) continue;
        dist[v] = dist[u] + 1;
        dfs(v, u);
        R[u] = ++times;
        p[times][0] = u;
    }
}
#define D(u, v, k) (dist[u] < dist[v] ? u : v)
void build_RMQ(){
    fx (i, 1, times) LG2[i] = Log2(i);
    fx (i, 1, LG2[times]) fx (j, 1, times - MASK(i) + 1)
        p[j][i] = D(p[j][i - 1], p[j + MASK(i - 1)][i - 1], i - 1);
}
int LCA(int l, int r){
    int lo = min(L[l], L[r]), hi = max(R[l], R[r]);
    int k = LG2[hi - lo + 1];
    return D(p[lo][k], p[hi - MASK(k) + 1][k], k);
}
void solve()
{
	cin >> n;
    fx (i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    build_RMQ();
