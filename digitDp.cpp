//https://toph.co/p/lids
#include <bits/stdc++.h>

typedef long double ld;

#define endl           "\n"
#define all(x)         x.begin(), x.end()
#define sz(x)          (int)(x).size()
#define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;


const int N=11;
int dp[N][N][N][2][2][2];
int solve(string &a,string &b,int i,bool bigA,bool smallB,bool start,int lastDig,int req) {
    if (i == a.length()) {
        return req == 0;
    }
    int &ans = dp[i][lastDig + 1][req][bigA][smallB][start];
    if (~ans)
        return ans;

    ans = 0;
    int l = 0, r = 9;
    if (!bigA) l = (a[i] - '0');
    if (!smallB) r = (b[i] - '0');
    for (int j = l; j <= r; j++) {
        bool n_bigA = bigA | (j > l);
        bool n_smallB = smallB | (j < r);
        bool n_start = (start | (j != 0));
        ans += solve(a, b, i + 1, n_bigA, n_smallB, n_start, lastDig, req);
        if (j > lastDig && req > 0 && n_start)
            ans += solve(a, b, i + 1, n_bigA, n_smallB, n_start, j, req - 1);
    }
    return ans;
}
int solve(int x,int y,int k) {
    string a = to_string(x);
    string b = to_string(y);
    reverse(all(a));
    while (sz(a) < sz(b)) {
        a += '0';
    }
    reverse(all(a));
    memset(dp, -1, sizeof dp);
    return solve(a, b, 0, false, false, false, -1, k);
}
void solve() {
    int x,y;
    cin>>x>>y;
    for(int j=10;j>=1;j--){
        int ans=solve(x,y,j);
        if(ans>0){
            cout<<j<<" "<<ans<<endl;
            return;
        }
    }
}

int32_t main() {
    nitin;
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case "<<i<<": ";
        solve();
    }
}
