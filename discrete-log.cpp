// find smallest x such that a^x==b %m
// O(sqrt(m))
// doesnt matter if a and m are coprime or not
// beware of a=0
int solve(int a,int b,int m) {
    a %= m;
    b %= m;
 
    if(a==0) {
        if (b == 0) return 1;
        return -1;
    }
 
    int k = 1, add = 0, g;
    while ((g = gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, ++add;
        k = (k * a / g) % m;
    }
 
    int n = sqrt(m) + 1;
    int an = 1;
    for (int i = 0; i < n; i++) {
        an *= a;
        an %= m;
    }
    unordered_map<int, int> vals;
    int cur = b;
    for (int j = 0; j <= n; j++) {
        vals[cur] = j;
        cur *= a;
        cur %= m;
    }
    cur = k;
    for (int j = 1; j <= n; j++) {
        cur *= an;
        cur %= m;
        if (vals.count(cur)) {
            return n * j - vals[cur] + add;
        }
    }
    return -1;
}
