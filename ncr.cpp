const int N=200001;
int fact[N];
int fact_inv[N];

int power(int x, int y, int p) {
    int res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
int modi(int a, int m) {
    return power(a, m - 2, m);
}
void pre() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    fact_inv[N-1]=modi(fact[N-1],mod);
    for(int i=N-2;i>=0;i--){
        fact_inv[i]=(fact_inv[i+1]*(i+1))%mod;
    }
}
int ncr(int n, int r) {
    if (r > n)
        return 0;
    return (fact[n] * ((fact_inv[r] * fact_inv[n - r]) % mod)) % mod;
}
