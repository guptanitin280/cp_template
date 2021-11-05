// O(nloglogn)
const int N=1000001;
bool prime[N];
void sieve() {
    for(auto &c:prime) c=true;
    prime[0] = prime[1] = false;
    for (int i = 2; i * i < N; i++) {
        if (prime[i]) {
            for (int j = i * i; j < N; j += i) {
                prime[j] = false;
            }
        }
    }
}
