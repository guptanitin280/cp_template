// one-base hld (? hot lady decomposition ) 
// https://codeforces.com/blog/entry/53170
const int N=200005;
vector<int>g[N];
segte s(N); //ds
int sz[N],par[N],head[N],child[N],tin[N],tout[N],tme,val[N];

void dfs_child(int node,int p){
    sz[node]=1;
    par[node]=p;
    head[node]=node;
    for(auto &c:g[node]){
        if(c!=p){
            dfs_child(c,node);
            sz[node]+=sz[c];
            if(sz[child[node]]<sz[c]) child[node]=c;
        }
    }
}
void dfs_hld(int node,int p){
    tin[node]=++tme;
    s.a[tme]=val[node]; // out value in ds

    if(child[node]){
        head[child[node]]=head[node];
        dfs_hld(child[node],node);
    }
    for(auto &c:g[node]){
        if(c!=p && c!=child[node]){
            dfs_hld(c,node);
        }
    }
    tout[node]=tme;
}
bool ancestor(int p,int u){
    return tin[p]<=tin[u] && tout[p]>=tout[u];
}
int lca(int u,int v){
    if(ancestor(u,v)) return u;
    if(ancestor(v,u)) return v;
    while(!ancestor(par[head[u]],v))  u=par[head[u]];
    while(!ancestor(par[head[v]],u))  v=par[head[v]];
    u=par[head[u]],v=par[head[v]];
    if(ancestor(u,v)) return v;
    else return u;
}
int query_up(int node,int l){
    int ans=0;
    while(head[node]!=head[l]){
        ans=max(ans,s.query(tin[head[node]],tin[node]).val);
        node=par[head[node]];
    }
    ans=max(ans,s.query(tin[l],tin[node]).val);
    return ans;
}
int query(int u,int v){
    int l=lca(u,v);
    return max(query_up(u,l), query_up(v,l));
}
void update(int node,int x){
    s.update(tin[node],x);
}

void init(){
    dfs_child(1,1);
    dfs_hld(1,1);
    s.build();
}

/***************************************************** old version ***************************************************************/
// //1-base-indexing
// const int N = 100001;
// const int M = 22;
// vector<int> v[N];
// int par[N][M], sz[N], dep[N], label[N], big_child[N], chain[N], a[N], timer;

// struct node {
//     int val;

//     node() {
//         val = 0;
//     }
// };

// class hld {
// public:
//     int n{};
//     vector<node> tree;
//     vector<int> lazy;
//     vector<bool> prsnt;
//     node neutral;

//     void init(int _n) {
//         n = _n + 1;
//         for (int i = 0; i < n; i++)
//             chain[i] = i;
//         timer = 1;
//         tree.resize(4 * n + 1);
//         lazy.assign(4 * n + 1, 0);
//         prsnt.assign(4 * n + 1, false);
//         dfs_size(1, 0, 0);
//         dfs_labels(1, 0);
//         dfs_chains(1, 0);
//         clc_par();
//     }

//     //merge function
//     static void merge(node &curr, node &left, node &right) {
//         curr.val = max(left.val, right.val);
//     }


//     void prop(int index, int ss, int se) {
//         tree[index].val += lazy[index];
//         if (ss != se) {
//             lazy[2 * index] += lazy[index];
//             lazy[2 * index + 1] += lazy[index];
//             prsnt[2 * index] = prsnt[2 * index + 1] = true;
//         }
//         lazy[index] = 0;
//         prsnt[index] = false;
//     }


//     node query(int index, int ss, int se, int qs, int qe) {
//         if (prsnt[index])
//             prop(index, ss, se);
//         if (qs > se || qe < ss) return neutral;
//         if (qs <= ss && qe >= se) return tree[index];
//         int mid = (ss + se) / 2;
//         node left = query(2 * index, ss, mid, qs, qe);
//         node right = query(2 * index + 1, mid + 1, se, qs, qe);
//         node mer;
//         merge(mer, left, right);
//         return mer;
//     }

//     node query(int l, int r) {
//         return query(1, 0, n - 1, l - 1, r - 1);
//     }

//     void update(int index, int ss, int se, int l, int r, int inc) {
//         if (prsnt[index])
//             prop(index, ss, se);
//         if (r < ss || l > se)
//             return;
//         if (ss >= l && se <= r) {
//             prsnt[index] = true;
//             lazy[index] += inc;
//             prop(index, ss, se);
//             return;
//         }
//         int mid = (ss + se) / 2;
//         update(2 * index, ss, mid, l, r, inc);
//         update(2 * index + 1, mid + 1, se, l, r, inc);
//         merge(tree[index], tree[2 * index], tree[2 * index + 1]);
//     }

//     void update(int l, int r, int inc) {
//         update(1, 0, n - 1, l - 1, r - 1, inc);
//     }

//     static void dfs_size(int node, int p, int d) {
//         sz[node] = 1;
//         dep[node] = d;
//         par[node][0] = p;
//         int big_c = -1, big_v = -1;
//         for (auto c:v[node]) {
//             if (c != p) {
//                 dfs_size(c, node, d + 1);
//                 sz[node] += sz[c];
//                 if (sz[c] > big_v) {
//                     big_c = c;
//                     big_v = sz[c];
//                 }
//             }
//         }
//         big_child[node] = big_c;
//     }

//     void dfs_labels(int node, int p) {
//         label[node] = timer++;
//         update(label[node], label[node], a[node]);
//         if (big_child[node] != -1) {
//             dfs_labels(big_child[node], node);
//         }
//         for (auto x:v[node]) {
//             if (x != p && x != big_child[node])
//                 dfs_labels(x, node);
//         }
//     }

//     static void dfs_chains(int node, int p) {
//         if (big_child[node] != -1) {
//             chain[big_child[node]] = chain[node];
//         }
//         for (auto x:v[node]) {
//             if (x != p) {
//                 dfs_chains(x, node);
//             }
//         }
//     }

//     int query_chain(int node, int lca) {
//         int value = 0;
//         while (dep[lca] < dep[node]) {
//             int top = chain[node];
//             if (dep[top] <= dep[lca]) {
//                 int Lab = label[node] - (dep[node] - dep[lca] - 1);
//                 return max(value, query(Lab, label[node]).val);
//             }
//             value = max(value, query(label[top], label[node]).val);
//             node = par[top][0];
//         }
//         return value;
//     }

//     int lca(int x, int y) {
//         if (dep[x] < dep[y])
//             swap(x, y);
//         int diff = dep[x] - dep[y];
//         for (int i = M - 1; i >= 0; i--) {
//             if (diff & (1 << i))
//                 x = par[x][i];
//         }
//         if (x == y) return x;
//         for (int i = M - 1; i >= 0; i--) {
//             if (par[x][i] != par[y][i]) {
//                 x = par[x][i];
//                 y = par[y][i];
//             }
//         }
//         return par[x][0];
//     }

//     int query_hld(int x, int y) {
//         int lc = lca(x, y);
//         int value = max(query_chain(x, lc), query_chain(y, lc));
//         return value;
//     }

//     void update_chain(int node, int lca, int inc) {
//         while (dep[lca] < dep[node]) {
//             int top = chain[node];
//             if (dep[top] <= dep[lca]) {
//                 int Lab = label[node] - (dep[node] - dep[lca] - 1);
//                 update(Lab, label[node], inc);
//                 return;
//             }
//             update(label[top], label[node], inc);
//             node = par[top][0];
//         }
//     }

//     int update_hld(int x, int y, int inc) {
//         int lc = lca(x, y);
//         update_chain(x, lc, inc);
//         update_chain(y, lc, inc);
//     }

//     void clc_par() {
//         for (int j = 1; j < M; j++) {
//             for (int i = 1; i <= n; i++) {
//                 par[i][j] = par[par[i][j - 1]][j - 1];
//             }
//         }
//     }
// };
//for edges:->
//vector<pair<int,int>>temp[N];
//void push(int node, int parent) {
//    for (auto c:temp[node]) {
//        if (c.f != parent) {
//            a[c.f] = c.s;
//            push(c.f, node);
//        }
//    }
//}
