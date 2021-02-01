//ax+by=c
int gcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int x1,y1;
    int d=gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}
bool solve(int a,int b,int c,int &x,int &y,int &g) {
    if(a==0 && b==0) {
        g = x = y = 0;
        return true;
    }
    g = gcd(abs(a), abs(b), x, y);
    if (c % g != 0) {
        return false;
    }
    x *= (c / g);
    y *= (c / g);
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}