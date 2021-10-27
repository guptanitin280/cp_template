const int N=200001;
const int M=21;
int par[N][M];
int n;
vector<int>g[N];
void dfs_par(int node,int p){
    par[node][0]=p;
    for(auto &c:g[node]){
        if(c!=p){
            dfs_par(c,node);
        }
    }
}
void fill(int root){
    dfs_par(root,-1);
    for(int j=1;j<M;j++){
        for(int i=0;i<n;i++){
            if(par[i][j-1]==-1) par[i][j]=-1;
            else par[i][j]=par[par[i][j-1]][j-1];
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
        int x,k;
        cin>>x>>k;
        --x;
        int node=get_kp(x,k);
        if(node!=-1) node++;
        cout<<node<<endl;
    }
}
