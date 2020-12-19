const int N=100001;
const int M=22;
int a[N];
int table[N][M];
int Log[N];
int n;
class sparse_table{
public:
    int n;
    explicit sparse_table(int _n){
        n=_n;
        for(int i=2;i<=n;i++){
            Log[i]=Log[i/2]+1;
        }
    }
    int f(int left,int right){
        return gcd(left,right);
    }
    void build(){
        for(int i=0;i<n;i++) table[i][0]=a[i];
        for(int j=1;j<M;j++){
            for(int i=0;i+(1<<j)<=n;i++){
                table[i][j]=f(table[i][j-1],table[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l,int r){ //for idempotent
        int j=Log[r-l+1];
        return f(table[l][j],table[r-(1<<j)+1][j]);
    }
//    int query(int l,int r){
//        int val=0;
//        for(int i=M-1;i>=0;i--){
//            if((1<<i)<=(r-l+1))
//            {
//                val=f(val,table[l][i]);
//                l+=(1<<i);
//            }
//        }
//        return val;
//    }

};