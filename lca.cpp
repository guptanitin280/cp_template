const int N=200001;
const int M=21;
int par[N][M];
int n;
vector<int>g[N];
int dep[N];

void dfs_par(int node,int p){
    par[node][0]=p;
    for(auto &c:g[node]){
        if(c!=p){
            dep[c]=dep[node]+1;
            dfs_par(c,node);
        }
    }
}
void fill(int root=0){
    dfs_par(root,root);
    for(int j=1;j<M;j++){
        for(int i=0;i<n;i++){
            par[i][j]=par[par[i][j-1]][j-1];
        }
    }
}
int get_kp(int node,int k){
    for(int j=M-1;j>=0;j--){
        if(k&(1ll<<j)){
            if(node!=-1)
                node=par[node][j];
        }
    }
    return node;
}
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    x= get_kp(x,dep[x]-dep[y]);
    if(x==y) return x;
    for(int j=M-1;j>=0;j--){
        if(par[x][j]!=par[y][j]){
            x=par[x][j];
            y=par[y][j];
        }
    }
    return par[x][0];
}
void solve() {
    int q;
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int val;
        cin>>val;
        --val;
        g[val].push_back(i);
        g[i].push_back(val);
    }
    fill(0);
    while(q--){
        int x,y;
        cin>>x>>y;
        --x;--y;
        cout<<lca(x,y)+1<<endl;
    }
}
