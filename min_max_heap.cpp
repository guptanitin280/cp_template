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


int level[101];
void pre() {
    level[1] = 0;
    for (int i = 2; i <= 100; i++) {
        level[i] = level[i / 2] + 1;
    }
    for (int i = 0; i < 100; i++) {
        level[i] = level[i + 1];
    }
}
class min_max_heap {
public:
    deque<int> dq;

    void insert(int val) {
        dq.push_back(val);
        shift_up(dq.size() - 1);
    }

    int get_min() {
        return dq[0];
    }

    int get_max() {
        return *max_element(dq.begin(), min(dq.end(), dq.begin() + 3));
    }

    void remove_min() {
        swap(dq[0], dq.back());
        dq.pop_back();
        shift_down(0);
    }

    void remove_max() {
        int idx = max_element(dq.begin(), min(dq.end(), dq.begin() + 3)) - dq.begin();
        swap(dq[idx], dq.back());
        dq.pop_back();
        shift_down(idx);
    }

    void build_heap(vector<int> &v) {
        for (auto &c:v) {
            dq.push_back(c);
        }
        for (int i = dq.size() - 1; i >= 0; i--) {
            shift_down(i);
        }
    }

    int par(int i) {
        return (i - 1) / 2;
    }

    void shift_up(int idx) {
        int curr = idx;
        if (curr > 0) {
            if (level[curr] % 2 == 0) {
                if (dq[curr] > dq[par(curr)]) {
                    swap(dq[curr], dq[par(curr)]);
                    shift_up_max(par(curr));
                } else {
                    shift_up_min(curr);
                }
            } else {
                if (dq[curr] < dq[par(curr)]) {
                    swap(dq[curr], dq[par(curr)]);
                    shift_up_min(par(curr));
                } else {
                    shift_up_max(curr);
                }
            }
        }
    }

    void shift_up_min(int idx) {
        if (level[idx] >= 2) {
            int g_idx = par(par(idx));
            if (g_idx >= 0) {
                if (dq[g_idx] > dq[idx]) {
                    swap(dq[g_idx], dq[idx]);
                    shift_up_min(g_idx);
                }
            }
        }
    }

    void shift_up_max(int idx) {
        if (level[idx] >= 2) {
            int g_idx = par(par(idx));
            if (g_idx >= 0) {
                if (dq[g_idx] < dq[idx]) {
                    swap(dq[g_idx], dq[idx]);
                    shift_up_max(g_idx);
                }
            }
        }
    }

    void shift_down(int idx) {
        if (level[idx] % 2 == 0) {
            shift_down_min(idx);
        } else {
            shift_down_max(idx);
        }
    }

    int child1(int idx) {
        return 2 * idx + 1;
    }

    int child2(int idx) {
        return 2 * idx + 2;
    }

    void shift_down_min(int idx) {
        int curr = idx;
        if (2 * curr + 1 < dq.size()) {
            vector<pair<int, int>> v;
            if (child1(curr) < dq.size()) {
                v.push_back({dq[child1(curr)], child1(curr)});
                if (child1(child1(curr)) < dq.size())
                    v.push_back({dq[child1(child1(curr))], child1(child1(curr))});
                if (child2(child1(curr)) < dq.size())
                    v.push_back({dq[child2(child1(curr))], child2(child1(curr))});
            }
            if (child2(curr) < dq.size()) {
                v.push_back({dq[child2(curr)], child2(curr)});
                if (child1(child2(curr)) < dq.size())
                    v.push_back({dq[child1(child2(curr))], child1(child2(curr))});
                if (child2(child2(curr)) < dq.size())
                    v.push_back({dq[child2(child2(curr))], child2(child2(curr))});
            }
            sort(all(v));
            int child = v[0].second;
            if (child == 2 * curr + 1 || child == 2 * curr + 2) {
                if (dq[child] < dq[curr]) {
                    swap(dq[child], dq[curr]);
                }
            } else {
                if (dq[child] < dq[curr]) {
                    swap(dq[child], dq[curr]);
                    if (dq[child] > dq[par(child)]) {
                        swap(dq[child], dq[par(child)]);
                    }
                    shift_down_min(child);
                }
            }
        }
    }

    void shift_down_max(int idx) {
        int curr = idx;
        if (2 * curr + 1 < dq.size()) {
            vector<pair<int, int>> v;
            if (child1(curr) < dq.size()) {
                v.push_back({dq[child1(curr)], child1(curr)});
                if (child1(child1(curr)) < dq.size())
                    v.push_back({dq[child1(child1(curr))], child1(child1(curr))});
                if (child2(child1(curr)) < dq.size())
                    v.push_back({dq[child2(child1(curr))], child2(child1(curr))});
            }
            if (child2(curr) < dq.size()) {
                v.push_back({dq[child2(curr)], child2(curr)});
                if (child1(child2(curr)) < dq.size())
                    v.push_back({dq[child1(child2(curr))], child1(child2(curr))});
                if (child2(child2(curr)) < dq.size())
                    v.push_back({dq[child2(child2(curr))], child2(child2(curr))});
            }
            sort(all(v), greater<>());
            int child = v[0].second;
            if (child == 2 * curr + 1 || child == 2 * curr + 2) {
                if (dq[child] > dq[curr]) {
                    swap(dq[child], dq[curr]);
                }
            } else {
                if (dq[child] > dq[curr]) {
                    swap(dq[child], dq[curr]);
                    if (dq[child] < dq[par(child)]) {
                        swap(dq[child], dq[par(child)]);
                    }
                    shift_down_max(child);
                }
            }
        }
    }
};
void solve() {
    pre();
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        v.push_back(rand() % 100);
    }
    min_max_heap pq;
    pq.build_heap(v);
    while (!pq.dq.empty()) {
        cout << pq.get_max() << endl;
        pq.remove_max();
    }
}

int32_t main() {
    nitin;

    solve();
}