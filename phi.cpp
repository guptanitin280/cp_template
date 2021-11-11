int phi(int n){
    int res=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            while(n%i==0){
                n/=i;
            }
            res-=res/i;
        }
    }
    if(n>1) res-=res/n;
    return res;
}
