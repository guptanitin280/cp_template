void solve() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>>e;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        --a;--b;
        e.push_back({a,b,-c});
    }
    int d[n];
    for(int i=0;i<n;i++) d[i]=inf;
    d[0]=0;
    for(int i=0;i<n-1;i++){
        for(auto &c:e){
            if(d[c[0]]!=inf && d[c[1]]>d[c[0]]+c[2]){
                d[c[1]]=d[c[0]]+c[2];
            }
        }
    }
    for(int i=0;i<n-1;i++){
        for(auto &c:e){
            if(d[c[0]]!=inf && d[c[1]]>d[c[0]]+c[2]){
                d[c[1]]=ninf;
            }
        }
    }
    if(d[n-1]==ninf){
        cout<<-1<<endl;
    }else{
        cout<<-d[n-1]<<endl;
    }
}
