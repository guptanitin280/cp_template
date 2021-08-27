int Log[1001];
int table[11][11][1001][1001];
int a[1001][1001];
class sparseTable{
public:
    int n,m;
    sparseTable(int _n,int _m){
        n=_n;
        m=_m;
        for(int i=2;i<=1000;i++){
            Log[i]=Log[i/2]+1;
        }
    }
    int f(int x=0,int y=0,int z=0,int w=0){
        return max({x,y,z,w});
    }
    void init(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                table[0][0][i][j]=a[i][j];
            }
        }
        for(int row=0;row<n;row++){
            for(int j=1;j<=10;j++){
                for(int col=0;col+(1<<j)<=m;col++){
                    table[0][j][row][col]=f(table[0][j-1][row][col],table[0][j-1][row][col+(1<<(j-1))]);
                }
            }
        }
        for(int col=0;col<m;col++){
            for(int j=1;j<=10;j++){
                for(int row=0;row+(1<<j)<=n;row++){
                    table[j][0][row][col]=f(table[j-1][0][row][col],table[j-1][0][row+(1<<(j-1))][col]);
                }
            }
        }
        for(int i=1 ;i<=10;i++){
            for(int j=1;j<=10;j++){
                for(int x=0;x+(1<<i)<=n;x++){
                    for(int y=0;y+(1<<j)<=m;y++){
                        table[i][j][x][y]=f(
                                table[i-1][j-1][x][y],
                                table[i-1][j-1][x+(1<<(i-1))][y],
                                table[i-1][j-1][x][y+(1<<(j-1))],
                                table[i-1][j-1][x+(1<<(i-1))][y+(1<<(j-1))]
                        );
                    }
                }
            }
        }
    }
    int query(int x,int y,int _x,int _y) { //for idempotent
        if (_x < x || _y < y) return 0;
        int i_x = Log[_x - x + 1];
        int i_y = Log[_y - y + 1];
        return f(table[i_x][i_y][x][y],
                 table[i_x][i_y][_x -(1 << (i_x)) + 1][y],
                 table[i_x][i_y][x][_y - (1 << i_y) + 1],
                 table[i_x][i_y][_x - (1 << (i_x)) + 1][_y - (1 << (i_y)) + 1]
        );
    }
};



// log value after indices
// const int N=1000;
// const int M=10;
// int tab[N+1][N+1][M+1][M+1];
// int a[N+1][N+1];
// int L[N+1];

// struct st{
//     int n,m;
//     st(int _n,int _m){
//         n=_n;
//         m=_m;
//         for(int i=2;i<=N;i++){
//             L[i]=L[i/2]+1;
//         }
//     }
//     int f(int x,int y,int z=0,int w=0){
//         return max({x,y,z,w});
//     }
//     void build(){
//         for(int i=0;i<n;i++){
//             for(int j=0;j<m;j++){
//                 tab[i][j][0][0]=a[i][j];
//             }
//         }
//         for(int x=1;x<=M;x++){
//             for(int i=0;i<n;i++){
//                 for(int j=0;j<m;j++){
//                     if(i+(1<<x)-1<n){
//                         tab[i][j][x][0]=f(tab[i][j][x-1][0],tab[i+(1<<(x-1))][j][x-1][0]);
//                     }
//                 }
//             }
//         }
//         for(int y=1;y<=M;y++){
//             for(int i=0;i<n;i++){
//                 for(int j=0;j<m;j++){
//                     if(j+(1<<y)-1<m){
//                         tab[i][j][0][y]=f(tab[i][j][0][y-1],tab[i][j+(1<<(y-1))][0][y-1]);
//                     }
//                 }
//             }
//         }
//         for(int x=1;x<=M;x++){
//             for(int y=1;y<=M;y++){
//                 for(int i=0;i<n;i++){
//                     for(int j=0;j<m;j++){
//                         if(i+(1<<x)-1<n && j+(1<<y)-1<m){
//                             tab[i][j][x][y]=f(
//                                     tab[i][j][x-1][y-1],
//                                     tab[i+(1<<(x-1))][j][x-1][y-1],
//                                     tab[i][j+(1<<(y-1))][x-1][y-1],
//                                     tab[i+(1<<(x-1))][j+(1<<(y-1))][x-1][y-1]
//                                     );
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     // for idempotent function
//     int qry(int x,int y,int _x,int _y){
//         // neutral element
//         if(_x<x || _y<y) return 0;
//         int lx=L[_x-x+1];
//         int ly=L[_y-y+1];
//         return f(
//                 tab[x][y][lx][ly],
//                 tab[_x-(1<<lx)+1][y][lx][ly],
//                 tab[x][_y-(1<<ly)+1][lx][ly],
//                 tab[_x-(1<<lx)+1][_y-(1<<ly)+1][lx][ly]
//                 );
//     }
// };
