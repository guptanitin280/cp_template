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

// O(n)
const int N=200001;
int d[N];
vector<int>p;
void sieve(){
    for(int i=1;i<N;i++) d[i]=i;
    for(int i=2;i<N;i++){
        if(d[i]==i) p.push_back(i);
        for(auto &c:p){
            if(c>d[i] || i*c>=N) break;
            d[i*c]=c;
        }
    }
}
