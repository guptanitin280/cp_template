class dsu {
public:
    vector<int> parent;
    vector<int> size;
    vector<int>rank;

    explicit dsu(int a) {
        parent.resize(a);
        size.resize(a);
        rank.resize(a);
        for (int i = 0; i < a; i++) {
            parent[i] = i;
            size[i] = 1;
            rank[i]=0;
        }
    }

    int par(int i) {
        if (i == parent[i])
            return i;
        return parent[i] = par(parent[i]);
    }

    bool unite(int a, int b) {
        a = par(a);
        b = par(b);
        if (a != b) {
            if (rank[a] > rank[b])
                swap(a, b);
            parent[a] = b;
            size[b] += size[a];
            size[a] = 0;
            if (rank[a] == rank[b])
                rank[b]++;
            return true;
        }
        return false;
    }
};