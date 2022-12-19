class fenteRange {
public:
    int n;
    vector<int> tree[2];

    void init(int _n) {
        n = _n;
        tree[0].resize(n + 5, 0);
        tree[1].resize(n + 5, 0);
    }

    void upd(int which, int idx, int inc) {
        for (int j = idx; j <= n; j += j & -j) {
            tree[which][j] += inc;
        }
    }

    void range_upd(int l, int r, int x) {
        upd(0, l, x);
        upd(0, r + 1, -x);
        upd(1, l, x * (l - 1));
        upd(1, r + 1, -x * r);
    }

    int qry(int which, int idx) {
        int tot = 0;
        for (int j = idx; j <= n; j += j & -j) {
            tot += tree[which][j];
        }
        return tot;
    }

    int prefix_qry(int idx) {
        return qry(0, idx) * idx - qry(1, idx);
    }
};