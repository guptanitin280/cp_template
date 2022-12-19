//https://codeforces.com/blog/entry/85714
#include <bits/stdc++.h>

typedef long double ld;
#define int long long

#define gcd            __gcd
#define endl           "\n"
#define setbits(x)     __builtin_popcountll(x)
#define zrobits(x)     __builtin_ctzll(x)
#define mod            1000000007
#define mod2           998244353
#define maxe           *max_element
#define mine           *min_element
#define inf            1e18
#define pb             push_back
#define all(x)         x.begin(), x.end()
#define f              first
#define s              second
#define lb             lower_bound
#define ub             upper_bound
#define ins            insert
#define sz(x)          (int)(x).size()
#define mk             make_pair
#define deci(x, y)     fixed<<setprecision(y)<<x
#define w(t)           int t; cin>>t; while(t--)
#define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define PI             3.141592653589793238
#define mem0(x)        memset(x,0,sizeof x)
#define mem1(x)        memset(x,-1,sizeof x)
#define pr             pair<int,int>
#define vi             vector<int>
#define vvi            vector<vi>
#define vpr            vector<pr>
using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.f << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NITIN
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

/*

*/

struct node{
    int val;
    int idx;
    node()
    {
        val=0;
    }
};
class segte {
public:
    int n;
    vector<node> tree;
    vector<int> a;
    node neutral;

    void init(int N) {
        n = N;
        tree.resize(4 * n + 1);
        //default values
        a.assign(n, 0);
        neutral.val=INT_MIN;
    }

    void put(vector<int> &val) {
        a = val;
    }

    //merge function
    void merge(node &curr, node &left, node &right) {
        if (left.val > right.val) {
            curr.val = left.val;
            curr.idx = left.idx;
        } else {
            curr.val = right.val;
            curr.idx = right.idx;
        }
    }

    //for leaf
    void single(node &curr, int idx) {
        curr.val = a[idx];
        curr.idx = idx;
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

    void update(int idx,int delta) {
        a[idx]=delta;
        update(1, idx, 0, n - 1);
    }
};

const int N=200001;
const int M=300001;
int u[M],v[M]; // edge
vector<int> g[2*N]; // reachability tree
int par[2*N]; // parent in reachability tree
int tin[2*N],tout[2*N]; // euler tour on reachability tree
int tme=-1;
int nodes;

void init(int n) {
    nodes = n;
    for (int i = 0; i < n; i++) {
        par[i] = i;
    }
}

int get_par(int node) {
    if (node == par[node]) return node;
    return par[node] = get_par(par[node]);
}

bool addEdge(int e) {
    int a = get_par(u[e]);
    int b = get_par(v[e]);
    if (a == b) return false;
    par[nodes] = nodes;
    par[a] = nodes;
    par[b] = nodes;
    g[nodes].push_back(a);
    g[nodes].push_back(b);
    g[a].push_back(nodes);
    g[b].push_back(nodes);
    nodes++;
    return true;
}

void dfs(int node,int p) {
    tin[node] = ++tme;
    for (auto &c: g[node]) {
        if (c != p) {
            dfs(c, node);
        }
    }
    tout[node] = tme;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> queries;
    for (int i = 0; i < m; i++) {

        cin >> u[i] >> v[i];
        --u[i];
        --v[i];
    }
    bool vis[m];
    memset(vis, false, sizeof vis);
    vector<int> all;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        --y;
        queries.push_back({x, y});
        if (x == 2) {
            vis[y] = true;
        }

    }

    init(n);
    for (int i = 0; i < m; i++) {
        if (!vis[i]) {
            addEdge(i);
        }
    }

    int val[q];
    for (int i = q - 1; i >= 0; i--) {
        if (queries[i].f == 2) {
            addEdge(queries[i].second);
        } else {
            val[i] = get_par(queries[i].second);
        }
    }
    segte s;
    s.init(nodes + 5);
    s.build();
    for (int i = 0; i < nodes; i++) {
        if (i == get_par(i)) {
            dfs(i, -1);
        }
    }

    int which[nodes];
    for (int i = 0; i < nodes; i++) {
        which[tin[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        s.update(tin[i], a[i]);
    }


    for (int i = 0; i < q; i++) {
        if (queries[i].first == 1) {
            auto temp = s.query(tin[val[i]], tout[val[i]]);
            cout << temp.val << endl;
            s.update(temp.idx, 0);
        }
    }
}

int32_t main() {
    nitin;

    solve();
}