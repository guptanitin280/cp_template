int prime[1000001];
void sieve() {
    mem1(prime);
    prime[0] = prime[1] = 0;
    for (int i = 2; i <= 1000000; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= 1000000; j += i) {
                prime[j] = 0;
            }
        }
    }
}