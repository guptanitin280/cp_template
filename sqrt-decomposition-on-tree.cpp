//  INDEX[p[i]]<INDEX[i]
// https://www.hackerrank.com/challenges/subtrees-and-paths/problem
// tle :(
const int N=100010;
const int B=300;
vector<int>g[N],block[N/B+4],ng[N]; // only in block edges
int p[N],lvl[N],root[N],val[N],a[N],tin[N],tout[N],lazy[N/B+4];
int tme=-1;
int n;

void ett_1(int node,int par){
    tin[node]=++tme;
    p[node]=par;
    block[tin[node]/B].push_back(node);
    for(auto &c:g[node]){
        if(c!=par){
            ett_1(c,node);
        }
    }
    tout[node]=tme;
}

void dfs(int node){
    for(auto &c:ng[node]){
        lvl[c]=lvl[node]+1;
        root[c]=root[node];
        val[c]=max(val[node],a[c]);
        dfs(c);
    }
}

void process(int i){
    for(auto node:block[i]){
        if(p[node]==-1 || tin[node]/B!=tin[p[node]]/B){
            lvl[node]=0;
            root[node]=node;
            val[node]=a[node];
            dfs(node);
        }
    }
}

void upd_st(int node,int inc){
    int l=tin[node],r=tout[node];
    if(l/B==r/B){
        for(auto &c:block[l/B]){
            if(tin[c]>=tin[node] && tout[c]<=tout[node]){
                a[c]+=inc;
            }
        }
        process(l/B);
    }else{
        for(auto &c:block[l/B]){
            if(tin[c]>=tin[node] && tout[c]<=tout[node]){
                a[c]+=inc;
            }
        }
        process(l/B);

        for(auto &c:block[r/B]){
            if(tin[c]>=tin[node] && tout[c]<=tout[node]){
                a[c]+=inc;
            }
        }
        process(r/B);
        for(int i=(l/B)+1;i<(r/B);i++){
            lazy[i]+=inc;
        }
    }
}
int qry_path(int u,int v){
    int ans=INT_MIN;
    while(root[u]!=root[v]){
        if(tin[u]>tin[v]) swap(u,v);
        ans=max(ans,val[v]+lazy[tin[v]/B]);
        v=p[root[v]];
    }
    if(lvl[u]>lvl[v]) swap(u,v);

    int bn=tin[v]/B;
    while(lvl[v]>lvl[u]) ans=max(ans,a[v]+lazy[bn]),v=p[v];
    while(v!=u) ans=max(ans,max(a[v],a[u])+lazy[bn]),u=p[u],v=p[v];
    ans=max(ans,a[u]+lazy[bn]);
    // u is lca of given(u,v)
    return ans;
}




void init(int src){
    ett_1(src,-1);
    for(int i=0;i<n;i++){
        if(p[i]!=-1 && tin[p[i]]/B==tin[i]/B){
            ng[p[i]].push_back(i);
        }
    }
    int num_block=(n+B-1)/B;
    for(int i=0;i<num_block;i++){
        process(num_block);
    }
}

void solve() {
    cin>>n;
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    init(0);
    int q;
    cin>>q;
    int cnt=0;
    while(q--){
        string s;
        cin>>s;
        if(s=="add"){
            int node,inc;
            cin>>node>>inc;
            --node;
            upd_st(node,inc);
        }else{
            int x,y;
            cin>>x>>y;
            --x;--y;
            cout<<qry_path(x,y)<<endl;
        }
    }
}
