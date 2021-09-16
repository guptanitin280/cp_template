struct sd{
    vector<int>a,bv,bno,bl,br;
    int n,bsz,bcnt;

    sd(int _n,vector<int>&_a){
        n=_n;
        bsz=sqrt(n);
        bcnt=(n+bsz-1)/bsz;

        a=_a;
        bno.resize(n,0);

        bl.resize(bcnt,-1);
        br.resize(bcnt,-1);
        bv.resize(bcnt,0);

        for(int i =0;i<n;i++){
            bno[i]=i/bsz;
            if(bl[bno[i]]==-1) bl[bno[i]]=i;
            br[bno[i]]=i;

            bv[bno[i]]+=a[i];
        }
    }

    void upd(int i,int x){
        bv[bno[i]]-=a[i];
        a[i]=x;
        bv[bno[i]]+=a[i];
    }

    int qry(int l,int r){
        int tot=0;
        if(bno[l]==bno[r]){
            for(int j=l;j<=r;j++){
                tot+=a[j];
            }
        }else{
            for(int j=l;j<=br[bno[l]];j++){
                tot+=a[j];
            }
            for(int j=bno[l]+1;j<bno[r];j++){
                tot+=bv[j];
            }
            for(int j=bl[bno[r]];j<=r;j++){
                tot+=a[j];
            }
        }
        return tot;
    }

};
