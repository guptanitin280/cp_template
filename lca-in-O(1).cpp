//https://cses.fi/problemset/task/1688/
const int N=200005;
const int M=21;
int tin[N],tout[N],lvl[N],tab[2*N][M],L[2*N];
int tme=-1;
vector<int>g[N];
vector<int>ord;

void eut_3(int node,int p){
    tin[node]=++tme;
    ord.push_back(node);
    for(auto &c:g[node]){
        if(c!=p){
            lvl[c]=lvl[node]+1;
            eut_3(c,node);
            ++tme;
            ord.push_back(node);
        }
    }
    tout[node]=tme;
}
void fill(){
    eut_3(0,-1);
    for(int i=2;i<=sz(ord);i++){
        L[i]=L[i/2]+1;
    }
    for(int i=0;i<sz(ord);i++){
        tab[i][0]=ord[i];
    }
    for(int j=1;j<M;j++){
        for(int i=0;i+(1<<j)-1<sz(ord);i++){
            int x=tab[i][j-1];
            int y=tab[i+(1<<(j-1))][j-1];
            if(lvl[x]<lvl[y]){
                tab[i][j]=x;
            }else{
                tab[i][j]=y;
            }
        }
    }
}
int lca(int u,int v){
    if(tin[u]>tin[v]) swap(u,v);
    int l=tin[u],r=tin[v];
    int lg=L[r-l+1];
    int x=tab[l][lg];
    int y=tab[r-(1<<lg)+1][lg];
    if(lvl[x]<lvl[y]){
        return x;
    }else{
        return y;
    }

}
void solve() {
    int n,q;
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int val;
        cin>>val;
        --val;
        g[val].push_back(i);
        g[i].push_back(val);
    }
    fill();
    while(q--){
        int x,y;
        cin>>x>>y;
        --x;--y;
        cout<<lca(x,y)+1<<endl;
    }
}
