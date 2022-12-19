struct edge{
    int u,v,cost;
};
const int N=2501;
int d[N];
int par[N];
int n;
vector<edge>e;

vector<int> negative_cycle_in_graph() {
    for (int i = 0; i < n; i++) {
        d[i] = 0;
    }

    int x;
    for (int i = 0; i < n - 1; i++) {
        bool any = false;
        x = -1;
        for (auto &c: e) {
            if (d[c.u] != inf && d[c.v] > d[c.u] + c.cost) {
                d[c.v] = d[c.u] + c.cost;
                par[c.v] = c.u;
                any = true;
                x = c.v;
            }
        }
        if (!any) break;
    }

    if (x == -1)
        return {};
    for (int i = 0; i < n; i++) x = par[x];
    vector<int> path;
    while (path.empty() || x != path.front()) {
        path.push_back(x);
        x = par[x];
    }
    reverse(all(path));
    path.push_back(path.front());
    return path;
}