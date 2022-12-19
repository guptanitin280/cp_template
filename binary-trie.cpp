class node {
public:
    int left, right, cnt;

    node() {
        left = 0, right = 0, cnt = 0;
    }
};

class BT{
public:
    vector<node>t;
    int M;

    BT(int m=30):M(m) {
        t.emplace_back();
    }

    void insert(int num) {
        int idx = 0;
        t[idx].cnt++;
        for (int i = M; i >= 0; i--) {
            if (num & (1ll << i)) {
                if (!t[idx].right) {
                    t[idx].right = sz(t);
                    t.emplace_back();
                }
                idx = t[idx].right;
            } else {
                if (!t[idx].left) {
                    t[idx].left = sz(t);
                    t.emplace_back();
                }
                idx = t[idx].left;
            }
            t[idx].cnt++;
        }
    }

    bool isPresent(int num) {
        int idx = 0;
        for (int i = M; i >= 0; i--) {
            if (num & (1ll << i)) {
                if ((!t[idx].right) || (t[t[idx].right].cnt == 0)) {
                    return false;
                }
                idx = t[idx].right;
            } else {
                if ((!t[idx].left) || (t[t[idx].left].cnt == 0)) {
                    return false;
                }
                idx = t[idx].left;
            }
        }
        return true;
    }

    bool remove(int num) {
        if (!isPresent(num)) return false;
        int idx = 0;
        t[idx].cnt--;
        for (int i = M; i >= 0; i--) {
            if (num & (1ll << i)) {
                idx = t[idx].right;
            } else {
                idx = t[idx].left;
            }
            t[idx].cnt--;
        }
        return true;
    }

    int min_xor(int num) {
        int ans = 0;
        int idx = 0;
        if (t[idx].cnt == 0)
            return -1;

        for (int i = M; i >= 0; i--) {
            if (!(num & (1ll << i))) {
                if (t[idx].left &&( t[t[idx].left].cnt > 0)) {
                    idx = t[idx].left;
                } else {
                    ans |= (1ll << i);
                    idx = t[idx].right;
                }
            } else {
                if (t[idx].right && (t[t[idx].right].cnt > 0)) {
                    idx = t[idx].right;
                } else {
                    ans |= (1ll << i);
                    idx = t[idx].left;
                }
            }
        }
        return ans;
    }
};