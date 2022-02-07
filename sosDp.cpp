// tf SOS dp

//https://cses.fi/problemset/task/1654/
#include <bits/stdc++.h>
using namespace std;
#define endl           "\n"
#define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)

const int N=(1<<20);
int f[N]; // frequency
int val1[N]; // number of y such that (y|x)=x;
int val2[N]; // the number of elements y such that x&y=x
int val3[N]; // number of y such that (y|x)=x;

// sos(i,j) means from ith consider 2^j elements ( assume containing only j bits ) 
void sos(int i,int j) {
    if (j == 0) {
        val1[i] = f[i], val2[i] = f[i], val3[i] = 0;
        return;
    }
    sos(i, j - 1);
    sos(i + (1 << (j - 1)), j - 1);
    int tot = 0;
    for (int x = i; x < i + (1 << (j - 1)); x++) {
        val1[x + (1 << (j - 1))] += val1[x];
        val2[x] += val2[x + (1 << (j - 1))];
        int q = val3[x + (1 << (j - 1))];
        int p = val3[x];
        val3[x] += q;
        val3[x + (1 << (j - 1))] = p;
        tot += f[x + (1 << (j - 1))];
    }
    for (int x = i; x < i + (1 << (j - 1)); x++) {
        val3[x + (1 << (j - 1))] += tot;
    }
}
void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]]++;
    }
    sos(0, 20);
    for (int j = 0; j < n; j++) {
        cout << val1[a[j]] << " " << val2[a[j]] << " " << val3[a[j]] << endl;
    }
}

int32_t main() {
    nitin;

    solve();
}
