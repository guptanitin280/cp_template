const int N=1010;
int n;
int cap[N][N];
vector<int>ug[N];
int par[N];
int vis[N];
int bfs(int s,int t) {
    mem1(par);
    par[s]=0;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});
    while (!q.empty()) {
        int node = q.front().f;
        int flow = q.front().s;
        q.pop();
        for (auto c:ug[node]) {
            if (par[c] == -1 && cap[node][c] != 0) {
                par[c] = node;
                int c_flow = min(flow, cap[node][c]);
                if (c == t) {
                    return c_flow;
                }
                q.push({c, c_flow});
            }
        }
    }
    return 0;
}
int max_flow(int s,int t) {
    int tot_flow = 0;
    int curr_flow = 0;
    while ((curr_flow = bfs(s, t))) {
        tot_flow += curr_flow;
        int curr = t;
        while (curr != s) {
            int prev = par[curr];
            cap[prev][curr] -= curr_flow;
            cap[curr][prev] += curr_flow;
            curr = prev;
        }
    }
    return tot_flow;
}
vector<pair<int,int>>edges;
void dfs(int node,int p=0) {
    vis[node] = 1;
    for (auto c:ug[node]) {
        if (cap[node][c] && !vis[c]) {
            vis[c] = 1;
            dfs(c, node);
        }
    }
}