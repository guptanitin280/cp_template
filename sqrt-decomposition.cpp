class sd{
public:
    int n,bs,b_cnt;
    vector<int>a,b_val,b_no,bl,br;
    void init(int _n){

        n=_n;
        bs= sqrt(n);
        b_cnt=(n+bs-1)/bs;

        a.resize(n,0);
        b_val.resize(b_cnt,0);
        b_no.resize(n,0);
        bl.resize(b_cnt,-1);
        br.resize(b_cnt,0);
        for(int i=0;i<n;i++){
            b_no[i]=i/bs;
            if(bl[b_no[i]]==-1){
                bl[b_no[i]]=i;
            }
            br[b_no[i]]=i;
        }
    }
    void upd(int i,int x){
        b_val[b_no[i]]-=a[i];
        a[i]=x;
        b_val[b_no[i]]+=a[i];
    }
    int qry(int l,int r){
        int tot=0;
        if(b_no[l]==b_no[r]){
            for(int i=l;i<=r;i++) tot+=a[i];
        }else{
            for(int i=b_no[l]+1;i<b_no[r];i++)
                tot+=b_val[i];
            for(int i=l;i<=br[b_no[l]];i++)
                tot+=a[i];
            for(int i=bl[b_no[r]];i<=r;i++)
                tot+=a[i];
        }
        return tot;
    }
};
