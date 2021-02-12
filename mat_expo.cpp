class mat {
public:
    vector<vector<int>> m;
    int n;

    explicit mat(int _n) {
        n = _n;
        m.resize(n, vector<int>(n, 0));
    }

    mat operator*(mat const &b) {
        mat ans(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans.m[i][j] += m[i][k] * b.m[k][j]) %= mod;
                }
            }
        }
        return ans;
    }

    vector<int> operator*(vector<int>&b) const {
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                (ans[i] += m[i][j] * b[j])%=mod;
            }
        }
        return ans;
    }

    mat power(int p) {
        mat ans(n);
        mat curr = *this;
        for (int i = 0; i < n; i++) {
            ans.m[i][i] = 1;
        }
        while (p) {
            if (p & 1) {
                ans = ans * curr;
            }
            p /= 2;
            curr = curr * curr;
        }
        return ans;
    }
};