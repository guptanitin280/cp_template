//https://cp-algorithms.com/algebra/linear_congruence_equation.html
//smallest x that satisfy ax=b mod n
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
bool solve(int a,int b,int n,int &x) {
    int g = gcd(a, gcd(b, n));
    a /= g;
    b /= g;
    n /= g;
    int ai;
    if (modi(a, n, ai)) {
        x = (ai * b) % n;
        return true;
    } else {
        return false;
    }
}