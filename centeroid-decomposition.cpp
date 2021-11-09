// 1base
// better implementation, taking graph as set gives tle in some cases
// https://codeforces.com/problemset/problem/588/E

const int N = 100010, M = 22;
vector<int> eg[N]; //edge graph
int u[N],v[N];
set<int> a[N]; // node value
bool del[N];
int sz[N], c_par[N], level[N];
set<int> f[M][N]; // function that need to be calculated

int nodes = 0;
int adj(int e,int x){
    if(u[e]==x) return v[e];
    else return u[e];
}
void sz_cal(int node,int par=-1){
    nodes++;
    sz[node]=1;
    for(auto &e:eg[node]){
        int c=adj(e,node);
        if(del[e] || c==par) continue;
        sz_cal(c,node);
        sz[node]+=sz[c];
    }
}
int cent(int node,int par=-1){
    for(auto &e:eg[node]){
        int c=adj(e,node);
        if(del[e] || c==par) continue;
        if(sz[c]>(nodes)/2){
            return cent(c,node);
        }
    }
    return node;
}
// function calculation
set<int>unite(set<int>&a,set<int>&b){
    set<int>c;
    for(auto &e:a) c.insert(e);
    for(auto &e:b) c.insert(e);
    while(c.size()>10){
        c.erase(--c.end());
    }
    return c;
}
void dfs(int node,int par,int lvl,set<int>cur){
    f[lvl][node]=cur;
    for(auto &e:eg[node]){
        int c=adj(e,node);
        if(del[e] ||c==par) continue;
        dfs(c,node,lvl,unite(cur,a[c]));
    }
}
void decompose(int vert, int cent_par = 0) {
    nodes = 0;
    sz_cal(vert);
    int child = cent(vert);
    c_par[child] = cent_par;
    level[child] = level[cent_par] + 1;
    dfs(child,-1,level[child],a[child]); // function calculator

    for (auto e:eg[child]) {
        int c=adj(e,child);
        if(del[e]) continue;
        del[e]=true;
        decompose(c, child);
    }
}
int lca(int x,int y){
    if(level[x]>level[y]) swap(x,y);
    while(level[y]>level[x]) y=c_par[y];
    while(x!=y) x=c_par[x],y=c_par[y];
    return x;
}
set<int> qry(int x,int y){
    int l=lca(x,y);
    return unite(f[level[l]][x],f[level[l]][y]);
}

void solve() {
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=0;i<n-1;i++){
        cin>>u[i]>>v[i];
        eg[u[i]].push_back(i);
        eg[v[i]].push_back(i);
    }
    for(int i =0;i<m;i++){
        int val;
        cin>>val;
        a[val].insert(i+1);
        if(a[val].size()>10){
            a[val].erase(--a[val].end());
        }
    }
    decompose(1);
    while(q--){
        int x,y,cnt;
        cin>>x>>y>>cnt;
        set<int> ans= qry(x,y);
        int val=min(sz(ans),cnt);
        cout<<val<<" ";
        auto c=ans.begin();
        while(val>0){
            cout<<*c<<" ";
            c=next(c);
            val--;
        }
        cout<<endl;
    }
}

/***********************************************graph as set******************************************************/
// #include <bits/stdc++.h>

// typedef long double ld;
// #define int long long

// #define gcd            __gcd
// #define endl           "\n"
// #define setbits(x)     __builtin_popcountll(x)
// #define zrobits(x)     __builtin_ctzll(x)
// #define mod            1000000007
// #define mod2           998244353
// #define maxe           *max_element
// #define mine           *min_element
// #define inf            1e18
// #define pb             push_back
// #define all(x)         x.begin(), x.end()
// #define f              first
// #define s              second
// #define lb             lower_bound
// #define ub             upper_bound
// #define ins            insert
// #define sz(x)          (int)(x).size()
// #define mk             make_pair
// #define deci(x, y)     fixed<<setprecision(y)<<x
// #define w(t)           int t; cin>>t; while(t--)
// #define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)
// #define PI             3.141592653589793238
// #define mem0(x)        memset(x,0,sizeof x)
// #define mem1(x)        memset(x,-1,sizeof x)
// using namespace std;
// //every thing 1 base (https://codeforces.com/contest/161/problem/D)
// const int N = 100001, M = 22;
// set<int> v[N];
// int sz[N], cpar[N], level[N], dist[M][N], ans[N];
// int nodes = 0;

// void dfs(int node, int par, int lvl) {
//     nodes++;
//     sz[node] = 1;
//     dist[lvl][node] = dist[lvl][par] + 1;
//     for (auto c:v[node]) {
//         if (c == par)
//             continue;
//         dfs(c, node, lvl);
//         sz[node] += sz[c];
//     }
// }

// int cent(int node, int par = 0) {
//     for (auto c:v[node]) {
//         if (c == par)
//             continue;
//         if (sz[c] > (nodes / 2))
//             return cent(c, node);
//     }
//     return node;
// }

// void make(int vert, int cent_par = 0) {
//     nodes = 0;
//     dfs(vert, 0, level[cent_par]);
//     int child = cent(vert);
//     cpar[child] = cent_par;
//     level[child] = level[cent_par] + 1;
//     for (auto c:v[child]) {
//         v[c].erase(child);
//         make(c, child);
//     }
// }

// int lca(int u, int v) {
//     while (level[u] < level[v]) v = cpar[v];
//     while (level[u] > level[v]) u = cpar[u];
//     while (u != v) {
//         u = cpar[u];
//         v = cpar[v];
//     }
//     return u;
// }

// int distance(int u, int v) {
//     int l = lca(u, v);
//     return dist[level[l]][u] + dist[level[l]][v];
// }

// void update(int node) {
//     int u = node;
//     while (node != 0) {
//         ans[node] = min(ans[node], distance(node, u));
//         node = cpar[node];
//     }
// }

// int query(int node) {
//     int a = inf;
//     int u = node;
//     while (node != 0) {
//         a = min(a, ans[node] + distance(u, node));
//         node = cpar[node];
//     }
//     return a;
// }

// void solve() {
//     int n, m;
//     cin >> n >> m;
//     for (int i = 0; i <= n; i++) ans[i] = inf;
//     for (int i = 0; i < n - 1; i++) {
//         int a, b;
//         cin >> a >> b;
//         v[a].ins(b);
//         v[b].ins(a);
//     }
//     make(1);
//     update(1);
//     while (m--) {
//         int type;
//         cin >> type;
//         if (type == 1) {
//             int node;
//             cin >> node;
//             update(node);
//         } else {
//             int node;
//             cin >> node;
//             cout << query(node) << endl;
//         }
//     }
// }

// int32_t main() {
//     nitin;

//     solve();
// }
