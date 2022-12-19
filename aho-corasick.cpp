struct node{
    unordered_map<int,int>m;
    deque<int>occ;
    int link=0;
    int link_to_leaf=0;
    bool leaf=false;
    int len=0;
};

vector<node>trie(1);

void add(string &s){
    int which=0;
    for(auto &x:s) {
        int c=x-'a';
        if (!trie[which].m.count(c)) {
            trie.emplace_back();
            trie[which].m[c] = sz(trie) - 1;
        }
        which = trie[which].m[c];
    }
    trie[which].leaf=true;
    trie[which].len=s.length();
}

void make_suffix_link() {
    queue<int> q;
    for (auto &c: trie[0].m) {
        q.push(c.second);
    }
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (auto &c: trie[node].m) {
            int ch = c.first;
            int child = c.second;
            int k = trie[node].link;
            while (k != 0 && !trie[k].m.count(ch)) {
                k = trie[k].link;
            }
            if (trie[k].m.count(ch)) {
                k = trie[k].m[ch];
            }
            trie[child].link = k;
            if (trie[k].leaf) {
                trie[child].link_to_leaf = k;
            } else {
                trie[child].link_to_leaf = trie[k].link_to_leaf;
            }
            q.push(child);
        }
    }
}