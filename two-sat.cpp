struct twoSat {
    int n;
    vector<vector<int>> g, rg;
    vector<int> compNo, order, assignment;
    vector<bool> vis;

    twoSat(int _n) : n(_n) {
        g.assign(2 * n, vector<int>());
        rg.assign(2 * n, vector<int>());
        compNo.resize(2 * n);
        vis.resize(2 * n);
        assignment.resize( n);
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    //atLeast one of them is true (xVy)=(~y->x) ^ (~x->y)
    void addOr(int u, bool nu, int v, bool nv) {
        assert(u<n && v<n);
        int x = u, nx = u;
        int y = v, ny = v;
        if (nu) x += n;
        else nx += n;
        if (nv) y += n;
        else ny += n;
        addEdge(ny, x);
        addEdge(nx, y);
    }

    //(x,nx) must be true
    void addTrue(int x,bool nx) {
        addOr(x, nx, x, nx);
    }

    //only one of them is true (xVy)^(~xV~y)
    void addXor(int u, bool nu, int v, bool nv) {
        addOr(u, nu, v, nv);
        addOr(u, !nu, v, !nv);
    }

    //both have to be same (~xVy)^(xV~y)
    void addSame(int u, bool nu, int v, bool nv) {
        addXor(u, !nu, v, nv);
    }

    void dfs(int node) {
        vis[node] = true;
        for (auto &c: g[node])
            if (!vis[c]) dfs(c);
        order.push_back(node);
    }

    void Rdfs(int node, int num) {
        vis[node] = true;
        compNo[node] = num;
        for (auto &c: rg[node]) {
            if (!vis[c]) Rdfs(c, num);
        }
    }

    bool check() {
        fill(all(vis), false);
        for (int i = 0; i < 2 * n; i++)
            if (!vis[i]) dfs(i);
        fill(all(vis), false);
        reverse(all(order));
        int num = 0;
        for (auto &c: order)
            if (!vis[c])
                Rdfs(c, num++);
        for (int i = 0; i < n; i++) {
            if (compNo[i] == compNo[i + n]) return false;
            assignment[i] = compNo[i] > compNo[i + n];
        }
        return true;
    }
};