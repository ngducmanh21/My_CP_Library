
// templates HLD vjp pro
// copyright : NDM
#pragma GCC optimize("O2")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, query, par[N], sz[N], pos[N], id, depth[N], head[N], W[N];
bool dd[N];
vector <int> adj[N];

struct Segment_Tree{
private:
	vector <int> it, lazy;

	void pushDown(int i, int l, int r) {
		int mid = (l + r)>>1, L = 0, R = 0;

		for (int j = 2*i; j <= 2*i + 1; j++) {
			if (j == 2*i) L = l, R = mid;
			else L = mid + 1, R = r;

			it[j] += (R - L + 1)*lazy[i];
			lazy[j] += lazy[i];
		}

		lazy[i] = 0;
	}

	void update(int i, int l, int r, int u, int v, int val) {
		if (l > v || r < u || u > v) return;
		if (u <= l && r <= v) {
			it[i] += (r - l + 1)*val;
			lazy[i] += val;
			return;
		}

		int mid = (l + r)>>1;
		pushDown(i, l, r);

		update(i<<1, l, mid, u, v, val);
		update(i<<1|1, mid + 1, r, u, v, val);
		it[i] = it[i<<1] + it[i<<1|1];
	}

	int get(int i, int l, int r, int u, int v) {
		if (l > v || r < u || u > v) return 0;
		if (u <= l && r <= v) return it[i];

		pushDown(i, l, r);
		int mid = (l + r)>>1;
		int L = get(i<<1, l, mid, u, v);
		int R = get(i<<1|1, mid + 1, r, u, v);

		return L + R;
	}

public:
	Segment_Tree(int _n = 0) {
		n = _n;
		it.resize(4*n + 7, 0);
		lazy.resize(4*n + 7, 0);
	}

	void update(int l, int r, int val) {
		update(1, 1, n, l, r, val);
	}

	int get(int l, int r) {
		return get(1, 1, n, l, r);
	}

} myit;


void dfs(int u) {

	sz[u] = 1;
	int szz = adj[u].size(), iMax = 0, szMax = 0;

	for (int i = 0; i < szz; i++) {
		int v = adj[u][i];
		if (v == par[u]) continue;
		par[v] = u; dfs(v);
		sz[u] += sz[v];

		if (szMax < sz[v]) {
			szMax = sz[v];
			iMax = i;
		}
	}

	swap(adj[u][0], adj[u][iMax]);
}

void dfs_HLD(int u) {

	pos[u] = ++id;
	for (auto v:adj[u]) {
		if (v == par[u]) continue;

		if (2*sz[v] >= sz[u] - 1 && dd[u] == 0)
			dd[u] = 1, head[v] = head[u], depth[v] = depth[u];
		else head[v] = v, depth[v] = depth[u] + 1;

		dfs_HLD(v);
	}

}


int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);

	while (depth[u] > depth[v]) u = par[head[u]];

	while (head[u] != head[v]) {
		u = par[head[u]];
		v = par[head[v]];
	}

	if (pos[u] > pos[v]) swap(u, v);
	return u;
}

void update(int u, int v, int val) {
	if (depth[u] < depth[v]) swap(u, v);

	while (depth[u] > depth[v]) {
		myit.update(pos[head[u]] + 1, pos[u], val);
		W[head[u]] += val;
		u = par[head[u]];
	}

	while (head[u] != head[v]) {
		myit.update(pos[head[u]] + 1, pos[u], val);
		W[head[u]] += val;
		myit.update(pos[head[v]] + 1, pos[v], val);
		W[head[v]] += val;
		u = par[head[u]];
		v = par[head[v]];
	}

	if (pos[u] > pos[v]) swap(u, v);
	myit.update(pos[u] + 1, pos[v], val);
}

int get(int u, int v) {

	int ans = 0;
	if (depth[u] < depth[v]) swap(u, v);

	while (depth[u] > depth[v]) {
		ans += myit.get(pos[head[u]] + 1, pos[u]);
		ans += W[head[u]];
		u = par[head[u]];
	}

	while (head[u] != head[v]) {
		ans += myit.get(pos[head[u]] + 1, pos[u]);
		ans += W[head[u]];
		ans += myit.get(pos[head[v]] + 1, pos[v]);
		ans += W[head[v]];
		u = par[head[u]];
		v = par[head[v]];
	}

	if (pos[u] > pos[v]) swap(u, v);
	ans += myit.get(pos[u] + 1, pos[v]);
	return ans;
}

int main() {
	freopen("TASK.inp", "r", stdin);
	freopen("TASK.out", "w", stdout);

	cin >> n >> query;
	for (int i = 1; i <= n - 1; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1); head[1] = depth[1] = 1; dfs_HLD(1);
	myit = Segment_Tree(n);

	while (query--) {
		char task; int u, v;
		cin >> task >> u >> v;
		if (task == 'P') update(u, v, 1);
		else cout << get(u, v) << '\n';
	}
}
