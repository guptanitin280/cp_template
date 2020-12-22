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