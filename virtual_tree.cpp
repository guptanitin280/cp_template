const int N=200001;
const int M=21;
int par[N][M];
int n;
vector<pair<int,int>>g[N];
vector<pair<int,int>>ag[N];
int dep[N];
int dist[N];
int tin[N];
int tout[N];
int tme=-1;
void dfs_par(int node,int p){
    tin[node]=++tme;
    par[node][0]=p;
    for(auto c:g[node]){
        if(c.first!=p){
            dep[c.first]=dep[node]+1;
            dist[c.first]=dist[node]+c.second;
            dfs_par(c.first,node);
        }
    }
    tout[node]=++tme;
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
bool cmp(int a,int b){
    return tin[a]<tin[b];
}
bool anc(int x,int y){
    return tin[x]<=tin[y] && tout[x]>=tout[y];
}
void create_ag(vector<int>&v){
    sort(v.begin(),v.end(),cmp);
    int k=v.size();
    for(int i=0;i+1<k;i++){
        v.push_back(lca(v[i],v[i+1]));
    }
    sort(v.begin(),v.end(),cmp);
    v.resize(distance(v.begin(), unique(v.begin(),v.end())));
    for(auto &c:v){
        ag[c].clear();
    }
    stack<int>s;
    s.push(v[0]);
    for(int i=1;i<v.size();i++){
        while(!anc(s.top(),v[i])) s.pop();
        ag[v[i]].emplace_back(s.top(),dist[v[i]]-dist[s.top()]);
        ag[s.top()].emplace_back(v[i],dist[v[i]]-dist[s.top()]);
        s.push(v[i]);
    }
}
