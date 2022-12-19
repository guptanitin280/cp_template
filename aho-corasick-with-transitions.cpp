struct node {
    int link = -1;
    int ch;
    int p = -1;
    int val = 0;
    int dpVal=-1;
    int next[26], go[26];

    node(int p = -1, int ch = -1) : p(p), ch(ch) {
        memset(go, -1, sizeof go);
        memset(next, -1, sizeof next);
    }
};

struct AC {
    vector<node> trie;

    AC() {
        trie.emplace_back();
    }

    void add(string &s, int b) {
        int cur = 0;
        for (auto &c: s) {
            int ch = c - 'a';
            if (trie[cur].next[ch] == -1) {
                trie[cur].next[ch] = sz(trie);
                trie.emplace_back(cur, ch);
            }
            cur = trie[cur].next[ch];
        }
        trie[cur].val += b;
    }

    int get_link(int idx) {
        if (trie[idx].link == -1) {
            if (idx == 0 || trie[idx].p == 0) {
                trie[idx].link = 0;
            } else {
                trie[idx].link = go(get_link(trie[idx].p), trie[idx].ch);
            }
        }
        return trie[idx].link;
    }

    int get_dp(int idx) {
        if (idx == 0) return 0;
        if (trie[idx].dpVal == -1) {
            trie[idx].dpVal = trie[idx].val + get_dp(get_link(idx));
        }
        return trie[idx].dpVal;
    }

    int go(int idx, int ch) {
        if (trie[idx].go[ch] == -1) {
            if (trie[idx].next[ch] != -1) {
                trie[idx].go[ch] = trie[idx].next[ch];
            } else if (idx == 0) {
                trie[idx].go[ch] = 0;
            } else {
                trie[idx].go[ch] = go(get_link(idx), ch);
            }
        }
        return trie[idx].go[ch];
    }
};