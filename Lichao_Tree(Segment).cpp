struct Segment_Tree {
	int n;
	struct Line {
		long long a; long long b;

		long long get(int x) {
			return a * x + b;
		}
	} seg;

	vector <Line> it;

	Segment_Tree(int n) {
		this->n = n;
		it.resize(4 * n + 7);
	}

	void update(int i, int l, int r, int u, int v, Line &seg) {
		if (l > v || r < u) return;
		int mid = (l + r) >> 1;

		if (u <= l && r <= v) {
			// Y MAX

			if (it[i].get(l) >= seg.get(l) && it[i].get(r) >= seg.get(r)) {
				return;
			}

			if (it[i].get(l) <= seg.get(l) && it[i].get(r) <= seg.get(r)) {
				it[i] = seg;
				return;
			}

			if (it[i].get(l) >= seg.get(l) && it[i].get(mid) >= seg.get(mid)) {
				update(i << 1 | 1, mid + 1, r, u, v, seg);
				return;
			}

			if (it[i].get(l) <= seg.get(l) && it[i].get(mid) <= seg.get(mid)) {
				update(i << 1 | 1, mid + 1, r, u, v, it[i]);
				it[i] = seg;
				return;
			}

			if (it[i].get(r) >= seg.get(r) && it[i].get(mid + 1) >= seg.get(mid + 1)) {
				update(i << 1, l, mid, u, v, seg);
				return;
			}

			if (it[i].get(r) <= seg.get(r) && it[i].get(mid + 1) <= seg.get(mid + 1)) {
				update(i << 1, l, mid, u, v, it[i]);
				it[i] = seg;
				return;
			}

			return;
		}

		update(i << 1, l, mid, u, v, seg);
		update(i << 1 | 1, mid + 1, r, u, v, seg);
	}

	long long get(int i, int l, int r, int u) {
		if (l > u || r < u) return 0;
		long long res = it[i].get(u);
		if (l == r) return res;
		int mid = (l + r) >> 1;
		maximize(res, get(i << 1, l, mid, u));
		maximize(res, get(i << 1 | 1, mid + 1, r, u));
		return res;
	}
};
