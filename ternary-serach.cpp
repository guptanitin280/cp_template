    int l=0;
    int r=1e9+1;
    while(r-l>3){
        int mid=(l+r)/2;
        if(f(mid)>f(mid+1))
            l=mid+1;
        else
            r=mid;
        dbg(l,r);
    }
    int ans=inf;
    for(int i =l;i<=r;i++)
        ans=min(ans,f(i));
    cout<<ans<<endl;