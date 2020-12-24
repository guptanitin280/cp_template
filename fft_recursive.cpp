using cd = complex<ld>;
const ld PI = acos(-1);

void fft(vector<cd> &a, bool inverse) {
    int n = a.size();
    if (n == 1) return;
    vector<cd> even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }
    fft(even, inverse);
    fft(odd, inverse);

    ld theta = 2 * PI / n * (inverse ? -1 : 1);
    cd w_j(1);
    cd w_theta(cos(theta), sin(theta));
    for (int j = 0; j < n / 2; j++) {
        a[j] = even[j] + w_j * odd[j];
        a[j + n / 2] = even[j] - w_j * odd[j];
        if (inverse) {
            a[j] /= 2;
            a[j + n / 2] /= 2;
        }
        w_j *= w_theta;
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