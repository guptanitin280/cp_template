class dsu {
public:
    vector<int> parent;
    vector<int> size;
    stack<tuple<int, int, int, int>> stk;
    stack<int> flag;
    int comp = 0;

    explicit dsu(int a) {
        parent.resize(a);
        size.resize(a);
        comp = a;
        for (int i = 0; i < a; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int par(int i) {
        if (i == parent[i])
            return i;
        return parent[i] = par(parent[i]);
    }

    void unite(int a, int b) {
        a = par(a);
        b = par(b);
        if (a != b) {
            comp--;
            stk.push({a, b, size[a], parent[a]});
            parent[a] = b;
            size[b] += size[a];
            size[a] = 0;
        }
    }

    void save() {
        flag.push(stk.size());
    }

    void roll_back() {
        int a = get<0>(stk.top());
        int b = get<1>(stk.top());
        int sz = get<2>(stk.top());
        int rp = get<3>(stk.top());
        stk.pop();
        comp++;
        parent[a] = rp;
        size[a] = sz;
        size[b] -= size[a];
    }

    void roll() {
        int last = flag.top();
        flag.pop();
        while (stk.size() > last)
            roll_back();
    }
};