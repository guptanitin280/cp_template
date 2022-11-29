
const int N=200001;
int phi[N];

//let p1,p2,p3....pk be the prime factors of n
//applying inclusion and exclusion 
//then phi[n]=n-n/p1-n/p2....-n/pk + n/(p1*p2) + n/(p2*p3) .....
//clubbing-> phi[n]=n(1-1/p1)(1-1/p2)...(1-1/pk)
void etf(){
    for(int i=0;i<N;i++) phi[i]=i;
    for(int i=2;i<N;i++){
        if(phi[i]==i){
            for(int j=i;j<N;j+=i){
                phi[j]-=phi[j]/i;
            }
        }
    }
}

//using divisor sum property
//eg: divisors of 10-> 1,2,5,10 -> phi[1]+phi[2]+phi[5]+phi[10]=10
void etf(int n) {
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
}
