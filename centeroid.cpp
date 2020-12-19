vector<int>v[100001];
int sz[100001];
int n;
vector<int>centroid;
void cent(int node,int par) {
    sz[node] += 1;
    bool flag = true;
    for (auto c:v[node]) {
        if (c != par) {
            cent(c, node);
            sz[node] += sz[c];
            if (sz[c] > n / 2)
                flag = false;
        }
    }
    if (n - sz[node] > n / 2)
        flag = false;
    if (flag)
        centroid.pb(node);
}