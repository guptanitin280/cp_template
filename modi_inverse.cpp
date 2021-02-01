int gcd(int a,int b,int &x,int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}
bool modi(int a,int m,int &ai) {
    int x, y;
    int g = gcd(a, m, x, y);
    if (g != 1) {
        return false;
    } else {
        ai = (x % m + m) % m;
    }
    return true;
}