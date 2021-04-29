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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.f << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NITIN
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int n;
vector<pair<int,int>>v;
int dp[101][101];
int par[101][101];
int mat_chain(int l,int r) {
    if (dp[l][r] != INT_MAX)
        return dp[l][r];
    int ans = inf;
    int idx = -1;
    for (int j = l; j < r; j++) {
        int val = mat_chain(l, j) + mat_chain(j + 1, r) + v[l].f * v[j].s * v[r].s;
        if (val < ans) {
            ans = val;
            idx = j;
        }
    }
    par[l][r] = idx;
    return dp[l][r] = ans;
}
string solve(int l,int r) {
    if (l == r) {
        return to_string(l);
    }
    int idx = par[l][r];
    return "(" + solve(l, idx) + ")" + "(" + solve(idx + 1, r) + ")";
}
void solve() {
    cin >> n;
    memset(par, 0, sizeof par);
    for (auto &c:dp) {
        for (auto &d:c)
            d = INT_MAX;
    }
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        int a, b;
        cin >> a >> b;
        v.pb({a, b});
    }
    mat_chain(0, n - 1);
    cout << dp[0][n - 1] << endl;
    cout << solve(0, n - 1) << endl;
}

int32_t main() {
    nitin;

    solve();
}