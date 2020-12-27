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
using namespace std;
//every thing 1 base (https://codeforces.com/contest/161/problem/D)
const int N = 100001, M = 22;
set<int> v[N];
int sz[N], cpar[N], level[N], dist[M][N], ans[N];
int nodes = 0;

void dfs(int node, int par, int lvl) {
    nodes++;
    sz[node] = 1;
    dist[lvl][node] = dist[lvl][par] + 1;
    for (auto c:v[node]) {
        if (c == par)
            continue;
        dfs(c, node, lvl);
        sz[node] += sz[c];
    }
}

int cent(int node, int par = 0) {
    for (auto c:v[node]) {
        if (c == par)
            continue;
        if (sz[c] > (nodes / 2))
            return cent(c, node);
    }
    return node;
}

void make(int vert, int cent_par = 0) {
    nodes = 0;
    dfs(vert, 0, level[cent_par]);
    int child = cent(vert);
    cpar[child] = cent_par;
    level[child] = level[cent_par] + 1;
    for (auto c:v[child]) {
        v[c].erase(child);
        make(c, child);
    }
}

int lca(int u, int v) {
    while (level[u] < level[v]) v = cpar[v];
    while (level[u] > level[v]) u = cpar[u];
    while (u != v) {
        u = cpar[u];
        v = cpar[v];
    }
    return u;
}

int distance(int u, int v) {
    int l = lca(u, v);
    return dist[level[l]][u] + dist[level[l]][v];
}

void update(int node) {
    int u = node;
    while (node != 0) {
        ans[node] = min(ans[node], distance(node, u));
        node = cpar[node];
    }
}

int query(int node) {
    int a = inf;
    int u = node;
    while (node != 0) {
        a = min(a, ans[node] + distance(u, node));
        node = cpar[node];
    }
    return a;
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) ans[i] = inf;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        v[a].ins(b);
        v[b].ins(a);
    }
    make(1);
    update(1);
    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int node;
            cin >> node;
            update(node);
        } else {
            int node;
            cin >> node;
            cout << query(node) << endl;
        }
    }
}

int32_t main() {
    nitin;

    solve();
}