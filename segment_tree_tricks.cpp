// tested
// point update and max-min query
struct node {
    int max_val;
    int min_val;
    int one_cnt;

    node() : max_val(INT_MIN), min_val(INT_MAX),one_cnt(0) {

    }
};
class segte {
public:
    int n;
    vector<node> tree;
    vector<int> a;
    node neutral;

    segte(int N) : n(N) {
        tree.resize(4 * n + 1);
        a.resize(n);
    }

    void merge(node &curr, node &left, node &right) {
        curr.max_val = max(left.max_val, right.max_val);
        curr.min_val = min(left.min_val, right.min_val);
        curr.one_cnt = left.one_cnt + right.one_cnt;
    }

    void single(node &curr, int idx) {
        curr.min_val = a[idx];
        curr.max_val = a[idx];
        curr.one_cnt = (a[idx] == 1);
    }

    void build(int index, int ss, int se) {
        if (ss == se) {
            single(tree[index], ss);
            return;
        }
        int mid = (ss + se) / 2;
        build(2 * index, ss, mid);
        build(2 * index + 1, mid + 1, se);
        merge(tree[index], tree[2 * index], tree[2 * index + 1]);
    }

    void build() {
        build(1, 0, n - 1);
    }

    node query(int index, int ss, int se, int qs, int qe) {
        if (qs > se || qe < ss) return neutral;
        if (qs <= ss && qe >= se) return tree[index];
        int mid = (ss + se) / 2;
        node left = query(2 * index, ss, mid, qs, qe);
        node right = query(2 * index + 1, mid + 1, se, qs, qe);
        node mer;
        merge(mer, left, right);
        return mer;
    }

    node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void update(int index, int idx, int ss, int se) {
        if (idx < ss || idx > se)
            return;
        if (ss == se) {
            single(tree[index], ss);
            return;
        }
        int mid = (ss + se) / 2;
        update(2 * index, idx, ss, mid);
        update(2 * index + 1, idx, mid + 1, se);
        merge(tree[index], tree[2 * index], tree[2 * index + 1]);
    }

    void update(int idx, int delta) {
        a[idx] = delta;
        update(1, idx, 0, n - 1);
    }

    // index of first element >=x in [0,n-1]
    int first_greater(int index, int ss, int se, int x) {
        if (tree[index].max_val < x) return -1;
        if (ss == se) {
            return ss;
        }
        int m = (ss + se) / 2;
        int temp = first_greater(2 * index, ss, m, x);
        if (temp != -1) return temp;
        return first_greater(2 * index + 1, m + 1, se, x);
    }

    // index of first element >=x in [ql,n-1]
    int first_greater(int index, int ss, int se, int x, int ql) {
        if (ql > se) return -1;
        if (tree[index].max_val < x) return -1;
        if (ss == se) {
            return ss;
        }
        int m = (ss + se) / 2;
        int temp = first_greater(2 * index, ss, m, x, ql);
        if (temp != -1) return temp;
        return first_greater(2 * index + 1, m + 1, se, x, ql);
    }

    int first_greater(int x, int ql = 0) {
        if (ql == 0) return first_greater(1, 0, n - 1, x);
        else return first_greater(1, 0, n - 1, x, ql);
    }

    // change every element in [qs,qe] with value <=p to INT_MAX
    // return the count of element changed
    // complexity is (number_of_element<=p in [qs,qe])*log(n)
    int change(int index, int ss, int se, int qs, int qe, int p) {
        if (tree[index].min_val > p) return 0;
        if (qs > se || qe < ss) return 0;
        if (ss == se) {
            a[ss] = INT_MAX;
            single(tree[index], ss);
            return 1;
        }
        int m = (ss + se) / 2;
        int left = change(2 * index, ss, m, qs, qe, p);
        int right = change(2 * index + 1, m + 1, se, qs, qe, p);
        merge(tree[index], tree[2 * index], tree[2 * index + 1]);
        return left + right;
    }

    int change(int qs, int qe, int p) {
        return change(1, 0, n - 1, qs, qe, p);
    }

    // kth one
    int get_kth(int index, int ss, int se, int k) {
        if (ss == se) {
            return ss;
        }
        int m = (ss + se) / 2;
        if (tree[2 * index].one_cnt >= k) return get_kth(2 * index, ss, m, k);
        else return get_kth(2 * index + 1, m + 1, se, k - tree[2 * index].one_cnt);
    }

    int get_kth(int k) {
        return get_kth(1, 0, n - 1, k);
    }

    // we can store complete subarray that a segment [l,r] cover, it will be O(nlogn) memory only
};


/*******************************************************************************************************************************************************************/


// calculate the count of non zero element in whole array, and supports inc,dec in a range [l,r]
const int N=1000000;
int add[4*N];
int tot[4*N];

void correct(int i,int s,int e) {
    if (add[i] > 0) tot[i] = (e - s + 1);
    else if (s == e) tot[i] = 0;
    else tot[i] = tot[2 * i] + tot[2 * i + 1];
}
void upd(int i,int s,int e,int l,int r,int inc) {
    if (r < s || l > e) return;
    if (s >= l && e <= r) {
        add[i] += inc;
        correct(i, s, e);
        return;
    }
    int m = (s + e) / 2;
    upd(2 * i, s, m, l, r, inc);
    upd(2 * i + 1, m + 1, e, l, r, inc);
    correct(i, s, e);
}
int qry() {
    return tot[1];
}


