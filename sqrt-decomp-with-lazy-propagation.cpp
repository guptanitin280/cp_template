struct sd{
    vector<int>a,bv,bno,bl,br,lazy;
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
        lazy.resize(bcnt,0);

        for(int i =0;i<n;i++){
            bno[i]=i/bsz;
            if(bl[bno[i]]==-1) bl[bno[i]]=i;
            br[bno[i]]=i;

            bv[bno[i]]+=a[i];
        }
    }

    void prop(int block_num){
        
        if(lazy[block_num]==0){
            return;
        }
        for(int j=bl[block_num];j<=br[block_num];j++){
            a[j]+=lazy[block_num];
        }
        bv[block_num]+=lazy[block_num]*(br[block_num]-bl[block_num]+1);
        lazy[block_num]=0;
    }

    void upd(int l,int r,int x){
        if(bno[l]==bno[r]){
            prop(bno[l]);
            for(int j=l;j<=r;j++){
                a[j]+=x;
                bv[bno[l]]+=x;
            }
        }else{
            prop(bno[l]);
            for(int j=l;j<=br[bno[l]];j++){
                a[j]+=x;
                bv[bno[l]]+=x;
            }
            for(int j=bno[l]+1;j<bno[r];j++){
                lazy[j]+=x;
            }
            prop(bno[r]);
            for(int j=bl[bno[r]];j<=r;j++){
                a[j]+=x;
                bv[bno[r]]+=x;
            }
        }
    }

    int qry(int l,int r){
        int tot=0;
        if(bno[l]==bno[r]){
            prop(bno[l]);
            for(int j=l;j<=r;j++){
                tot+=a[j];
            }
        }else{
            prop(bno[l]);
            for(int j=l;j<=br[bno[l]];j++){
                tot+=a[j];
            }
            for(int j=bno[l]+1;j<bno[r];j++){
                tot+=bv[j];
                tot+=lazy[j]*(br[j]-bl[j]+1);
            }
            prop(bno[r]);
            for(int j=bl[bno[r]];j<=r;j++){
                tot+=a[j];
            }
        }
        return tot;
    }

};
