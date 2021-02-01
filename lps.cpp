vector<int> lps(string &s) {
    int n = sz(s);
    vector<int> f(n, 0);
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j])
            j = f[j - 1];
        if (s[i] == s[j])
            j++;
        f[i] = j;
    }
    //count of all prefix function
//    vector<int>cnt(n+1,0);
//    for(int i=0;i<n;i++){
//        cnt[f[i]]++;
//    }
//    for(int i=n-1;i>0;i--){
//        cnt[f[i-1]]+=cnt[i];
//    }
//    //if whole string also counted
//    for(int i=0;i<=n;i++){
//        cnt[i]+=1;
//    }
    return f;
}