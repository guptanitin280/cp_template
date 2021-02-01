//1-base //better to use 2 hashes
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
struct Hash{
    vector<int>pref;
    vector<int>pows;
    vector<int>i_pows;
    int p,m;
    Hash(string &s,int _p,int _m): p(_p) , m(_m)
    {
        int n=sz(s);
        pows.resize(n+1,0);
        pref.resize(n+1,0);
        i_pows.resize(n+1,0);
        pows[0]=1;
        int p_inv=modi(p,m);
        i_pows[0]=1;
        for(int i=1;i<=n;i++){
            pref[i]=(pref[i-1]+(s[i-1]-'a'+1)*pows[i-1])%m;
            pows[i]=(pows[i-1]*p)%m;
            i_pows[i]=(i_pows[i-1]*p_inv)%m;
        }
    }
    int get(int l,int r){
        return ((pref[r]-pref[l-1]+m)*i_pows[l-1])%m;
    }
};