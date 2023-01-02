//recursive

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

//iterative

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

//use case
//check for every len(b) in string A times ch1 and ch2 are equal (string character matching)
vector<int> find(string &a,string &b,char ch1,char ch2) {
    int n = a.size();
    int m = b.size();
    vector<int> poly1(n, 0), poly2(m, 0);
    for (int i = 0; i < n; i++) {
        poly1[i] = (a[i] == ch1);
    }
    for (int i = 0; i < m; i++) {
        poly2[m - i - 1] = (b[i] == ch2);
    }
    vector<int> ans = multiply(poly1, poly2); //fft
    vector<int> to_return;
    for (int i = m - 1; i <= n - 1; i++)
        to_return.push_back(ans[i]);
    return to_return;
}

