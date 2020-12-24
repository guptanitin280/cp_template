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