#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 1e18

//divide and conquer dp optimization
//works when dp[i][j]=min(dp[i-1][k]+cost(k+1,j))
// k<j

// condition to apply is opt(i,j) <= opt(i,j+1)
// one special case when above condition is true is
// when cost function satisfy the quadrangle property
// C(a,c)+C(b,d)<= C(a,d)+C(b,c) a<=b<=c<=d


//data structure to get the cost function
struct distinctPairs {
    vector<int> a;

    int n;
    int cur;
    vector<int> freq;
    int l, r;

    distinctPairs(int _n, vector<int> &_a) {
        a = _a;
        n = _n;
        freq.resize(n, 0);
        cur = 0;
        l = 0;
        r = 0;
        freq[a[0]]++;
    }

    void add(int idx) {
        cur += freq[a[idx]];
        freq[a[idx]]++;
    }

    void sub(int idx) {
        freq[a[idx]]--;
        cur -= freq[a[idx]];
    }

    void moveTo(int nL, int nR) {
        while (nL < l) {
            l--;
            add(l);
        }
        while (nR > r) {
            r++;
            add(r);
        }
        while (nL > l) {
            sub(l);
            l++;
        }
        while (nR < r) {
            sub(r);
            r--;
        }
    }

};

const int N=100001;
vector<int>dp_before(N),dp_cur(N);

void calculateDp(int l,int r,int optl,int optr,distinctPairs &p) {
    if (l > r) return;
    int m = (l + r) / 2;
    p.moveTo(optl, m);
    dp_cur[m] = min(p.cur + ((optl == 0) ? (int)inf : dp_before[optl - 1]), dp_cur[m]);
    int opt = optl;
    for (int j = optl + 1; j <= min(optr, m); j++) {
        p.moveTo(j, m);
        if (dp_cur[m] > dp_before[j - 1] + p.cur) {
            dp_cur[m] = dp_before[j - 1] + p.cur;
            opt = j;
        }
    }
    calculateDp(l, m - 1, optl, opt, p);
    calculateDp(m + 1, r, opt, optr, p);
}

int32_t main() {
    int n, k;
    cin >> n >> k;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        --val;
        a.push_back(val);
    }
    distinctPairs p(n,a);
    for(int i=0;i<n;i++) {
        p.moveTo(0, i);
        dp_cur[i] = p.cur;
    }

    for(int j=1;j<k;j++) {
        dp_before = dp_cur;
        for(int x=0;x<n;x++) {
            dp_cur[x] = inf;
        }
        calculateDp(0, n - 1, 0, n - 1,p);
    }
    cout<<dp_cur[n-1]<<endl;
}
//https://codeforces.com/contest/868/problem/F
