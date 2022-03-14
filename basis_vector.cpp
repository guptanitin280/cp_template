const int M = 31;
int basis[M];
int cnt;

void init() {
    memset(basis, 0, sizeof basis);
    cnt = 0;
}

bool insertVector(int val) {
    for (int j = M - 1; j >= 0; j--) {
        if (!(val & (1 << j))) continue;
        if (basis[j] == 0) {
            basis[j] = val;
            cnt++;
            return true;
        }
        val ^= basis[j];
    }
    return false;
}

int max_ele() {
    int ans = 0;
    for (int j = M - 1; j >= 0; j--) {
        if (ans & (1 << j)) continue;
        ans ^= basis[j];
    }
    return ans;
}
int kth_ele(int k){
    int ans=0;
    int rem=cnt;
    for(int j=M-1;j>=0;j--) {
        if (!basis[j]) continue;
        rem--;
        if (ans & (1 << j)) {
            if ((1 << rem) >= k) {
                ans ^= basis[j];
            }else{
                k-=(1<<rem);
            }
        } else {
            if ((1 << rem) < k) {
                ans ^= basis[j];
                k -= (1 << rem);
            }
        }
    }
    return ans;
}
bool is_in_space(int x) {
    for (int j = M - 1; j >= 0; j--) {
        if (!(x & (1 << j))) continue;
        if (!basis[j]) return false;
        x ^= basis[j];
    }
    return true;
}
