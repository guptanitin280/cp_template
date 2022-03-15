// https://cses.fi/problemset/task/2085/
// li chao tree, its like generalised CHT
struct line {
    int m, c;

    line(int _m = 0, int _c = inf) : m(_m), c(_c) {

    }

    int operator()(int x) const {
        return m * x + c;
    }
};
class lct {
public:
    vector<line> tree;
    int n;

    lct(int _n) : n(_n) {
        tree.resize(4 * n + 1);
    }

    int sgn(int x) {
        if (x == 0) return 0;
        if (x < 0) return -1;
        return 1;
    }

    void upd(int i, int s, int e, line l) {
        if (s == e) {
            if (l(s) < tree[i](s)) {
                tree[i] = l;
            }
            return;
        }
        int m = (s + e) / 2;

        int fir = (l(s) - tree[i](s));
        int sec = (l(m) - tree[i](m));
        if (sgn(fir) * sgn(sec) <= 0) {
            if (l(e) < tree[i](e))
                swap(tree[i], l);
            upd(2 * i, s, m, l);

        } else {
            if (l(m) < tree[i](m)) {
                swap(tree[i], l);
            }
            upd(2 * i + 1, m + 1, e, l);

        }
    }

    void upd(line l) {
        upd(1, 0, n - 1, l);
    }

    int qry(int i, int s, int e, int x) {
        if (s == e) {
            return tree[i](x);
        }
        int m = (s + e) / 2;
        if (x <= m)
            return min({tree[i](x), qry(2 * i, s, m, x)});
        else
            return min({tree[i](x), qry(2 * i + 1, m + 1, e, x)});
    }

    int qry(int x) {
        return qry(1, 0, n - 1, x);
    }
};
