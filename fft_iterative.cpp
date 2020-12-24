using cd = complex<ld>;
const ld PI = acos(-1);

void fft(vector<cd> &a, bool inverse) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = (n >> 1);
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ld theta = 2 * PI / len * (inverse ? -1 : 1);
        cd w_theta(cos(theta), sin(theta));
        for (int i = 0; i < n; i += len) {
            cd w_j(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w_j;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w_j *= w_theta;
            }
        }
    }
    if (inverse) {
        for (auto &c:a)
            c /= n;
    }
}

vector<int> multiply(vector<int> &a, vector<int> &b) {
    vector<cd> fa(all(a)), fb(all(b));
    int n = 1;
    while (n < sz(a) + sz(b))
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = round(fa[i].real());
    return ans;
}