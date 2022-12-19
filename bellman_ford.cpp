struct edge{
    int u,v,cost;
};
const int N=2501;
int d[N];
int par[N];
int n;
vector<edge>e;

void bellman_ford(int source) {
    for (int i = 0; i < n; i++) {
        d[i] = inf;
        par[i] = -1;
    }
    d[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool any = false;
        for (auto &c: e) {
            if (d[c.u] != inf && d[c.v] > d[c.u] + c.cost) {
                d[c.v] = d[c.u] + c.cost;
                par[c.v] = c.u;
                any = true;
            }
        }
        if (!any) break;
    }

    // put negative infinity to nodes having arbitrary small value
    for (int i = 0; i < n; i++) {
        bool any = false;
        for (auto &c: e) {
            if (d[c.u] != inf && d[c.v] > d[c.u] + c.cost) {
                d[c.v] = -inf;
                any = true;
            }
        }
        if (!any) break;
    }
}


/************************************** old code ********************************************/
//void solve() {
//    int n,m;
//    cin>>n>>m;
//    vector<vector<int>>e;
//    while(m--){
//        int a,b,c;
//        cin>>a>>b>>c;
//        --a;--b;
//        e.push_back({a,b,-c});
//    }
//    int d[n];
//    for(int i=0;i<n;i++) d[i]=inf;
//    d[0]=0;
//    for(int i=0;i<n-1;i++){
//        for(auto &c:e){
//            if(d[c[0]]!=inf && d[c[1]]>d[c[0]]+c[2]){
//                d[c[1]]=d[c[0]]+c[2];
//            }
//        }
//    }
//    for(int i=0;i<n-1;i++){
//        for(auto &c:e){
//            if(d[c[0]]!=inf && d[c[1]]>d[c[0]]+c[2]){
//                d[c[1]]=ninf;
//            }
//        }
//    }
//    if(d[n-1]==ninf){
//        cout<<-1<<endl;
//    }else{
//        cout<<-d[n-1]<<endl;
//    }
//}
