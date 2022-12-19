vector<int> prefF(string &s) {
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
    return f;
}

// count the frequency of all prefixes
vector<int> freq(string &s) {
    int n = sz(s);
    vector<int> f = prefF(s);

    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cnt[f[i]]++;
    }
    for (int i = n - 1; i > 0; i--) {
        cnt[f[i - 1]] += cnt[i];
    }
    for (int i = 0; i <= n; i++) {
        cnt[i] += 1;
    }
    return cnt;
}

// number of different substrings of string
int diffSubStr(string &s){
    int n=sz(s);
    int ans=0;
    for(int i=0;i<n;i++){
        string rs=s.substr(0,i+1);
        reverse(all(rs));
        vector<int>f=prefF(rs);
        int maxPrefF=maxe(all(f));
        ans+=i+1-maxPrefF;
    }
    return ans;
}

// period of string
int period(string &s) {
    int n = sz(s);
    vector<int> f = prefF(s);
    int per = n - f[n - 1];
    if (n % per != 0) {
        return n;
    }
    return per;
}

// automata over prefix function
// aut[i][j] gives prefix function value
// if previous prefix function values is i
// and j is the current character
vector<vector<int>> automata(string &s) {
    int n = sz(s);
    s += '#';
    vector<int> pf = prefF(s);
    vector<vector<int>> aut(n+1, vector<int>(26, 0));
    for (int i = 0; i <= n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i]) {
                aut[i][c] = aut[pf[i - 1]][c];
            } else {
                aut[i][c] = i + ('a' + c == s[i]);
            }
        }
    }
    return aut;
}