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

struct Hash {
    vector<int> pref;
    vector<int> pows;
    vector<int> i_pows;
    vector<int> pref_s;
    vector<int> pows_s;
    vector<int> i_pows_s;
    int p, m;
    int p_s, m_s;

    explicit Hash(string &s, int _p = 31, int _m = mod, int __p = 53, int __m = mod2) : p(_p), m(_m), p_s(__p),
                                                                                        m_s(__m) {
        int n = sz(s);
        pows.resize(n + 1, 0);
        pref.resize(n + 1, 0);
        i_pows.resize(n + 1, 0);
        pows_s.resize(n + 1, 0);
        pref_s.resize(n + 1, 0);
        i_pows_s.resize(n + 1, 0);
        pows[0] = 1;
        int p_inv = modi(p, m);
        i_pows[0] = 1;
        pows_s[0] = 1;
        int p_inv_s = modi(p_s, m_s);
        i_pows_s[0] = 1;
        for (int i = 1; i <= n; i++) {
            pref[i] = (pref[i - 1] + (s[i - 1] - 'a' + 1) * pows[i - 1]) % m;
            pows[i] = (pows[i - 1] * p) % m;
            i_pows[i] = (i_pows[i - 1] * p_inv) % m;
        }
        for (int i = 1; i <= n; i++) {
            pref_s[i] = (pref_s[i - 1] + (s[i - 1] - 'a' + 1) * pows_s[i - 1]) % m_s;
            pows_s[i] = (pows_s[i - 1] * p_s) % m_s;
            i_pows_s[i] = (i_pows_s[i - 1] * p_inv_s) % m_s;
        }
    }

    pair<int, int> get(int l, int r) {
        ++l;
        ++r;
        return {((pref[r] - pref[l - 1] + m) * i_pows[l - 1]) % m,
                ((pref_s[r] - pref_s[l - 1] + m_s) * i_pows_s[l - 1]) % m_s};
    }
};