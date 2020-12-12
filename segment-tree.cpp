struct node{
    //req variable
    int sum;
    //default value
    node()
    {
        sum=0;
    }
};
class segte {
public:
    int n{};
    vector<node> tree;
    vector<int> a;
    node neutral;

    void init(int N) {
        n = N;
        tree.resize(4 * n + 1);
        //default values
        a.assign(n, 0);
    }

    void put(vector<int> &val) {
        a = val;
    }

    //merge function
    void merge(node &curr, node &left, node &right) {
        curr.sum = left.sum + right.sum;
    }

    //for leaf
    void single(node &curr, int idx) {
        curr.sum = a[idx];
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

    void update(int idx) {
        update(1, idx, 0, n - 1);
    }
};