vector<pair<int,int>> factorise(int n){
    vector<pair<int,int>>ans;
    int cnt;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            cnt=0;
            while(n%i==0) n/=i,cnt++;
            ans.emplace_back(i,cnt);
        }
    }
    if(n!=1) ans.emplace_back(n,1);
    return ans;
}
