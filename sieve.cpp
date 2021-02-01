const int N=1000001;
bool prime[N];
void sieve() {
    mem1(prime);
    prime[0] = prime[1] = 0;
    for (int i = 2; i * i < N; i++) {
        if (prime[i]) {
            for (int j = i * i; j < N; j += i) {
                prime[j] = 0;
            }
        }
    }
}