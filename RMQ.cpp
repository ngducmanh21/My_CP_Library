template <typename T>
struct RMQ {
  vector <vector <T>> st;
  vector <T> a;
  int n;
 
  RMQ (int _n = 1) { 
    n = _n;
    a.assign(n + 5, 0);
    st.assign(n + 5, vector <T> (__lg(n) + 5, 0));
  }
 
  void ass (int id, T x) {
    a[id] = x;
  }
 
  T join (T a, T b) {
    return __gcd(a, b); // fit from here
  }
 
  void build() {
    for (int i = 1; i <= n; i++)
      st[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++) {
      for (int i = 1; i + (1 << j) - 1 <= n; i++)
        st[i][j] = join(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
 
  T get (int L, int R) {
    int j = __lg(R - L + 1);
    return join(st[L][j], st[R - (1 << j) + 1][j]);
  }
};