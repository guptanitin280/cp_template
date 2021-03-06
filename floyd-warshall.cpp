void solve() {
    int n,m,q;
    cin>>n>>m>>q;
    int dp[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dp[i][j]=inf;
        }
    }
    for(int i =0;i<n;i++)
        dp[i][i]=0;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        --a;--b;
        dp[a][b]=min(dp[a][b],c);
        swap(a,b);
        dp[a][b]=min(dp[a][b],c);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                dp[j][k]=min(dp[j][k],dp[j][i]+dp[i][k]);
            }
        }
    }
    while(q--){
        int a,b;
        cin>>a>>b;
        --a;--b;
        if(dp[a][b]!=inf)
            cout<<dp[a][b]<<endl;
        else
            cout<<-1<<endl;
    }
}