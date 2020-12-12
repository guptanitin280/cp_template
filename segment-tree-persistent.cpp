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
int build(int ss,int se)
{
    int node=++ptr;
    if(ss==se)
    {
        return node;
    }
    int m=(ss+se)/2;
    lc[node]=build(ss,m);
    rc[node]=build(m+1,se);
    return node;
}
int update(int old_node,int ss,int se,int pos)
{
    int new_node=++ptr;
    if(ss==se)
    {
        val[new_node]=val[old_node]+1;
        return new_node;
    }
    int m=(ss+se)/2;
    if(pos<=m)
    {
        lc[new_node]=update(lc[old_node],ss,m,pos);
        rc[new_node]=rc[old_node];
    }
    else{
        rc[new_node]=update(rc[old_node],m+1,se,pos);
        lc[new_node]=lc[old_node];
    }
    val[new_node]=val[lc[new_node]]+val[rc[new_node]];
    return new_node;
}
int query(int ith_node,int jth_node,int ss,int se,int kth)
{
    if(ss==se)
    {
        return ss;
    }
    int m=(ss+se)/2;
    int left=val[lc[jth_node]]-val[lc[ith_node]];
    if(left>=kth)
        return query(lc[ith_node],lc[jth_node],ss,m,kth);
    else
        return query(rc[ith_node],rc[jth_node],m+1,se,kth-left);
}
void init(int q)
{
    root[0]=build(0,Max);
    for(int i=1;i<=q;i++)
    {
        root[i]=update(root[i-1],0,Max,a[i-1]);
    }
}

int32_t main() {
    nitin;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>a[i];
    set<int>s;
    for(int i=0;i<n;i++)
    {
        s.ins(a[i]);
    }
    int start=0;
    map<int,int>comp;
    map<int,int>r_comp;
    for(auto c:s)
    {
        comp[c]=start++;
        r_comp[start-1]=c;
    }
    for(int i=0;i<n;i++)
    {
        a[i]=comp[a[i]];
    }
    Max=start;
    init(n);
    while(m--)
    {
        int i,j,k;
        cin>>i>>j>>k;
        cout<<r_comp[query(root[i-1],root[j],0,Max,k)]<<endl;
    }
    return 0;
}