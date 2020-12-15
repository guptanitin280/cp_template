int fact[300001];
int fact_inv[300001];

void pre() {
    fact[0] = 1;
    fact_inv[0] = 1;
    for (int i = 1; i <= 300000; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        fact_inv[i] = (fact_inv[i - 1] * modi(i, mod)) % mod;
    }
}

int ncr(int n, int r) {
    if (r > n)
        return 0;
    return (fact[n] * ((fact_inv[r] * fact_inv[n - r]) % mod)) % mod;
}