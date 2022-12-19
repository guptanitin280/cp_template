vector<int> kmp(string &s,string &pat) {
    string t = pat + '$' + s;
    int n = sz(t);
    vector<int> f(n, 0);
    vector<int> occ;
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && t[i] != t[j])
            j = f[j - 1];
        if (t[i] == t[j])
            j++;
        f[i] = j;
    }
    for (int i = sz(pat) + 1; i < n; i++) {
        if (f[i] == sz(pat))
            occ.pb(i - 2 * sz(pat));
    }
    return occ;
}