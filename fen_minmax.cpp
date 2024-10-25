
// Just use to get prefix OR suffix (...), please don't combine them
struct BIT {
  typedef pair <int, int> T;
  T func (T a, T b) {
    return max(a, b);
  }

  vector <T> fen;
  int n = 0;
  T unit;

  BIT (int _n = 0, T _unit = {0, 0}) {
    n = _n;
    unit = _unit;
    fen.assign(n + 5, unit);
  }

  void update_pref (int idx, T val) {
    assert (idx >= 1 && idx <= n);
    for (; idx <= n; idx += idx & -idx) {
      fen[idx] = func(fen[idx], val);
    }
  }

  T get_pref (int idx) {
    assert (idx >= 1 && idx <= n);
    T ans = unit;
    for (; idx > 0; idx -= idx & -idx) {
      ans = func(ans, fen[idx]);
    }
    return ans;
  }

  void update_suff (int idx, T val) {
    assert (idx >= 1 && idx <= n);
    for (; idx > 0; idx -= idx & -idx)
      fen[idx] = func(fen[idx], val);
  }

  T get_suff (int idx) {
    assert (idx >= 1 && idx <= n);
    T ans = unit;
    for (; idx <= n; idx += idx & -idx) {
      ans = func(ans, fen[idx]);
    }
    return ans;
  }
};