const int N=200000;
const int M = 21;
int tab[N+1][M+1];
int L[N+1];
int a[N];

struct st{
    int n;
    st(int _n){
        n=_n;
        for(int i=2;i<=n;i++){
            L[i]=L[i/2]+1;
        }
    }
    int f(int x,int y){
        return max(x,y);
    }
    void build(){
        for(int i=0;i<n;i++){
            tab[i][0]=a[i];
        }
        for(int j=1;j<=M;j++){
            for(int i=0;i<n;i++){
                if(i+(1<<j)-1<n){
                    tab[i][j]=f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
                }
            }
        }
    }
    // for non-idempotent function
    int qry(int l,int r){
        int len=r-l+1;
        int idx=l;
        //initialise it will neutral value
        int tot=0;
        for(int j=M;j>=0;j--){
            if(len&(1ll<<j)){
                tot=f(tot,tab[idx][j]);
                idx+=(1<<j);
            }
        }
        return tot;
    }
    // for idempotent function
    int qry_i(int l,int r){
        int lg=L[r-l+1];
        return f(tab[l][lg],tab[r-(1<<lg)+1][lg]);
    }
};
