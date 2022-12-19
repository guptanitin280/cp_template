#include <bits/stdc++.h>

typedef long double ld;
#define int long long
//mkthnum spoj
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

const int N=100001;
const int SZ=21*N;
int ptr=1;
int l[SZ],r[SZ],val[SZ],a[N];

int node(int left,int right) {
    int pos = ptr;
    l[pos] = left;
    r[pos] = right;
    // function
    val[pos] = val[left] + val[right];
    ptr++;
    return pos;
}
int leaf(int value) {
    int pos = ptr;
    l[pos] = r[pos] = 0;
    val[pos] = value;
    ptr++;
    return pos;
}

int build(int s,int e) {
    if (s == e) {
        return leaf(a[s]);
    }
    int m = (s + e) / 2;
    int left = build(s, m);
    int right = build(m + 1, e);
    return node(left, right);
}

int update(int old,int s,int e,int idx,int inc) {
    if (s == e) {
        return leaf(val[old] + inc);
    }
    int m = (s + e) / 2;
    int left, right;
    if (idx <= m) {
        left = update(l[old], s, m, idx, inc);
        right = r[old];
    } else {
        left = l[old];
        right = update(r[old], m + 1, e, idx, inc);
    }
    return node(left, right);
}

int query(int ith,int jth,int s,int e,int k) {
    if (s == e) {
        return s;
    }
    int m = (s + e) / 2;
    int leftVal = val[l[jth]] - val[l[ith]];
    if (leftVal >= k) {
        return query(l[ith], l[jth], s, m, k);
    } else {
        return query(r[ith], r[jth], m + 1, e, k - leftVal);
    }
}



void solve() {
    int n, q;
    cin >> n >> q;
    int root[n + 1];
    root[0] = build(0, n);
    map<int, int> m;
    map<int, int> rm;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        m[a[i]] = true;
    }
    int temp = 0;
    for (auto &c: m) {
        c.second = temp++;
        rm[temp - 1] = c.first;
    }
    for (int i = 0; i < n; i++) {
        a[i] = m[a[i]];
    }
    for (int i = 1; i <= n; i++) {
        root[i] = update(root[i - 1], 0, n, a[i - 1], 1);
    }
    for (int i = 0; i < q; i++) {
        int l, r, v;
        cin >> l >> r >> v;
        cout << rm[query(root[l - 1], root[r], 0, n, v)] << endl;
    }


}

int32_t main() {
    nitin;

    solve();
}

//for range update
//bool prsnt[SZ];
//int lazy[SZ];
//int lazyKid(int node,int x) {
//    int pos = ptr;
//    l[pos] = l[node];
//    r[pos] = r[node];
//    lazy[pos] = lazy[node];
//    prsnt[pos] = true;
//
//    //function
//    lazy[pos] += x;
//    val[pos] = val[node];
//    ptr++;
//    return pos;
//}
//int copyNode(int node) {
//    int pos = ptr;
//    l[pos] = l[node];
//    r[pos] = r[node];
//    lazy[pos] = lazy[node];
//    prsnt[pos] = prsnt[node];
//    val[pos] = val[node];
//    ptr++;
//    return pos;
//}
//void propagate(int node,int s,int e) {
//    val[node] += lazy[node] * (e - s + 1);
//    if (s != e) {
//        l[node] = lazyKid(l[node], lazy[node]);
//        r[node] = lazyKid(r[node], lazy[node]);
//    }
//    lazy[node] = 0;
//    prsnt[node] = false;
//}
//
//int update(int old,int s,int e,int p,int q,int x) {
//    if (q < s || p > e) {
//        if (!prsnt[old]) return old;
//        int curr = copyNode(old);
//        propagate(curr, s, e);
//        return curr;
//    }
//    if (s >= p && e <= q) {
//        int curr = lazyKid(old, x);
//        propagate(curr, s, e);
//        return curr;
//    }
//    int m = (s + e) / 2;
//    int left = update(l[old], s, m, p, q, x);
//    int right = update(r[old], m + 1, e, p, q, x);
//    return node(left, right);
//}



/*********************************************old version*****************************/

#include <bits/stdc++.h>

// mkthnum spoj
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
using namespace std;

const int Q=100001;
int Max=100000;
int root[Q],val[21*Q],lc[21*Q],rc[21*Q],a[Q];
int ptr=0;
int build(int ss,int se) {
    int node = ++ptr;
    if (ss == se) {
        return node;
    }
    int m = (ss + se) / 2;
    lc[node] = build(ss, m);
    rc[node] = build(m + 1, se);
    return node;
}
int update(int old_node,int ss,int se,int pos) {
    int new_node = ++ptr;
    if (ss == se) {
        val[new_node] = val[old_node] + 1;
        return new_node;
    }
    int m = (ss + se) / 2;
    if (pos <= m) {
        lc[new_node] = update(lc[old_node], ss, m, pos);
        rc[new_node] = rc[old_node];
    } else {
        rc[new_node] = update(rc[old_node], m + 1, se, pos);
        lc[new_node] = lc[old_node];
    }
    val[new_node] = val[lc[new_node]] + val[rc[new_node]];
    return new_node;
}
int query(int ith_node,int jth_node,int ss,int se,int kth) {
    if (ss == se) {
        return ss;
    }
    int m = (ss + se) / 2;
    int left = val[lc[jth_node]] - val[lc[ith_node]];
    if (left >= kth)
        return query(lc[ith_node], lc[jth_node], ss, m, kth);
    else
        return query(rc[ith_node], rc[jth_node], m + 1, se, kth - left);
}
void init(int q) {
    root[0] = build(0, Max);
    for (int i = 1; i <= q; i++) {
        root[i] = update(root[i - 1], 0, Max, a[i - 1]);
    }
}

int32_t main() {
    nitin;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    set<int> s;
    for (int i = 0; i < n; i++) {
        s.ins(a[i]);
    }
    int start = 0;
    map<int, int> comp;
    map<int, int> r_comp;
    for (auto c: s) {
        comp[c] = start++;
        r_comp[start - 1] = c;
    }
    for (int i = 0; i < n; i++) {
        a[i] = comp[a[i]];
    }
    Max = start;
    init(n);
    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        cout << r_comp[query(root[i - 1], root[j], 0, Max, k)] << endl;
    }
    return 0;
}