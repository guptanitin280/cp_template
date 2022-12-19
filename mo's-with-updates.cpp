//https://codeforces.com/contest/940/problem/F
const int N=100005;
const int bs=2500;
int freq[2*N];
int val[N];
int a[N];
int temp[N];

struct Query {
    int l, r, t;
    int lBno,rBno;
    int idx;
};
struct Updates{
    int p,x;
    int old_val;
};
Query qry[N];
Updates upd[N];
int L=-1,R=-1,T=0;

bool cmp(Query &p,Query &q) {
    if (p.lBno == q.lBno) {
        if (p.rBno == q.rBno) return p.t < q.t;
        return p.rBno < q.rBno;
    }
    return p.lBno < q.lBno;
}
void add(int x) {
    val[freq[x]]--;
    freq[x]++;
    val[freq[x]]++;
}
void remove(int x) {
    val[freq[x]]--;
    freq[x]--;
    val[freq[x]]++;
}
void update(int p,int x) {
    if (p >= L && p <= R) {
        remove(a[p]);
        add(x);
    }
    a[p] = x;
}

int get_answer() {
    int j = 1;
    while (val[j] > 0) j++;
    return j;
}

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> m;
    int st = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (!m.count(a[i])) m[a[i]] = st++;
        temp[i] = a[i] = m[a[i]];
    }

    /*********************************************************/
    int up = 0;
    int qr = 0;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            qry[qr].l = l;
            qry[qr].lBno = l / bs;
            qry[qr].r = r;
            qry[qr].rBno = r / bs;
            qry[qr].t = up;
            qry[qr].idx = qr;
            qr++;
        } else {
            int p, x;
            cin >> p >> x;
            if (!m.count(x)) m[x] = st++;
            x = m[x];
            --p;
            up++;
            upd[up].p = p;
            upd[up].old_val = temp[p];
            temp[p] = x;
            upd[up].x = temp[p];
        }
    }
    L = 0, R = 0, T = 0;
    add(a[L]);
    q = qr;
    int ans[q];
    sort(qry, qry + q, cmp);
    for (int i = 0; i < q; i++) {
        auto &c = qry[i];
        int l = c.l;
        int r = c.r;
        int t = c.t;
        while (T < t) {
            T++;
            update(upd[T].p, upd[T].x);
        }
        while (T > t) {
            update(upd[T].p, upd[T].old_val);
            T--;
        }
        while (R < r) {
            R++;
            add(a[R]);
        }
        while (L > l) {
            --L;
            add(a[L]);
        }

        while (R > r) {
            remove(a[R]);
            --R;
        }
        while (L < l) {
            remove(a[L]);
            ++L;
        }
        ans[c.idx] = get_answer();
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}