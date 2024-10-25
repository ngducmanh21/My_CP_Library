struct DSU {
  vector <int> par;

  DSU (int n = 0) {
    par.assign(n + 5, -1);
  }

  int root (int u) {
    if (par[u] < 0)
      return u;
    return par[u] = root(par[u]);
  }

  int size (int u) {
    return -par[root(u)];
  }

  bool join (int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v)
      return false;
    if (par[u] > par[v])
      swap(u, v);
    par[u] += par[v];
    par[v] = u;
    return true;
  }
};