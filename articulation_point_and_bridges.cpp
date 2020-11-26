#include<bits/stdc++.h>
using namespace std;
const int N=200001;
vector<int>gr[N];
int dis[N];
int low[N];
int tme;
set<int>art_p;
vector<pair<int,int>>bridge;
void dfs(int node,int par) {
    dis[node] = low[node] = tme++;
    int child = 0;
    for (auto c:gr[node]) {
        if (!dis[c]) {
            child++;
            dfs(c, node);
            low[node] = min(low[node], low[c]);
            if (par != -1 && low[c] >= dis[node]) {
                art_p.insert(node);
            }
            if (low[c] > dis[node]) {
                bridge.push_back({node, c});
            }
        } else if (c != par) {
            low[node] = min(low[node], dis[c]);
        }
    }
    if (par == -1 && child > 1)
        art_p.insert(1);
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
    tme = 1;
    dfs(0, -1);
    cout << "cut vertices" << endl;
    for (auto c:art_p) {
        cout << c << " ";
    }
    cout << endl;
    cout << "bridges" << endl;
    for (auto c:bridge) {
        cout << c.first << " " << c.second << endl;
    }
}
int main() {
    solve();
}