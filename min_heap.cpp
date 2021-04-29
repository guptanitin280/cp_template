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

class min_heap {
public:
    deque<int> dq;

    void insert(int val) {
        dq.push_back(val);
        shift_up(dq.size() - 1);
    }

    int top() {
        return dq[0];
    }

    void pop() {
        swap(dq[0], dq.back());
        dq.pop_back();
        shift_down(0);
    }

    void build_heap(vector<int> &v) {
        for (auto &c:v) {
            dq.push_back(c);
        }
        for (int i = dq.size() - 1; i >= 0; i--) {
            shift_down(i);
        }
    }

    void shift_up(int idx) {
        int curr = idx;
        while (curr > 0) {
            int par_idx = (curr - 1) / 2;
            if (dq[par_idx] > dq[curr]) {
                swap(dq[par_idx], dq[curr]);
                curr = par_idx;
            } else {
                break;
            }
        }
    }

    void shift_down(int idx) {
        int curr = idx;
        while (2 * curr + 1 < dq.size()) {
            int child = 2 * curr + 1;
            if (2 * curr + 2 < dq.size() && dq[2 * curr + 2] < dq[child]) {
                child = 2 * curr + 2;
            }
            if (dq[child] < dq[curr]) {
                swap(dq[child], dq[curr]);
                curr = child;
            } else {
                break;
            }
        }
    }
};
void solve() {
//    vector<int>v;
//    for(int i=0;i<20;i++){
//        v.push_back(rand()%100);
//    }
    min_heap pq;
//    pq.build_heap(v);
//    pq.insert(10);
//    pq.insert(9);
//    pq.insert(8);
//    pq.insert(324);
//    pq.insert(2);
//    pq.insert(11);
//    pq.insert(7);
//    pq.insert(5);
//    pq.insert(10000);
//    pq.insert(12);
//    pq.insert(13);
//    pq.insert(6);
//    pq.insert(14);
//    pq.insert(20);
    while(!pq.dq.empty()){
        cout<<pq.top()<<endl;
        pq.pop();
    }
}

int32_t main() {
    nitin;

    solve();
}