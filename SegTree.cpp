struct SegTree {
  SegTree *lf, *rt;
  long long sum;
  int max_val, lazy;
  int l, r;
 
  SegTree (int L = 1, int R = 0) {
    l = L, r = R;
    sum = 0, max_val = 0, lazy = 0;
    lf = rt = NULL;
  }
 
  void expand() {
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (lf == NULL)
      lf = new SegTree(l, mid);
    if (rt == NULL)
      rt = new SegTree(mid + 1, r);
  }
 
  void push_lazy() {
    if (l == r)
      return;
    expand();
 
    int mid = (l + r) >> 1;
 
    lf->sum += 1ll * (mid - l + 1) * lazy;
    rt->sum += 1ll * (r - mid) * lazy;
 
    lf->max_val += lazy;
    rt->max_val += lazy;
 
    lf->lazy += lazy;
    rt->lazy += lazy;
 
    lazy = 0;
  }
 
  void push_up() {
    max_val = max(lf->max_val, rt->max_val);
    sum = lf->sum + rt->sum;
  }
 
  void update (int u, int v, int delta) {
    if (v < l || r < u)
      return;
    if (u <= l && r <= v) {
      sum += 1ll * delta * (r - l + 1);
      max_val += delta;
      lazy += delta;
      return;
    }
    push_lazy();
    lf->update(u, v, delta);
    rt->update(u, v, delta);
    push_up();
  }
 
  pair <int, long long> get (int u, int v) {
    if (v < l || r < u)
      return {-2e9, 0};
    if (u <= l && r <= v)
      return {max_val, sum};
    push_lazy();
    auto [max_left, sum_left] = lf->get(u, v);
    auto [max_right, sum_right] = rt->get(u, v);
 
    return {max(max_left, max_right), sum_left + sum_right};
  }
};