const int N=200001;
int phi[N];
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
