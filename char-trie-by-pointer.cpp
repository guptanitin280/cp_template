struct node{
    char data;
    unordered_map<char,node*>child;
    bool terminal;
    explicit node(char d){
        data=d;
        terminal=false;
    }
};
class trie {
    node *root;
    int cnt;
public:
    trie() {
        root = new node('\0');
        cnt = 0;
    }

    void insert(const char *s) {
        node *temp = root;
        for (int i = 0; s[i] != '\0'; i++) {
            if (!temp->child.count(s[i])) {
                temp->child[s[i]] = new node(s[i]);
            }
            temp = temp->child[s[i]];
        }
        temp->terminal = true;
    }

    bool find(const char *s) {
        node *temp = root;
        for (int i = 0; s[i] != '\0'; i++) {
            if (!temp->child.count(s[i]))
                return false;
            temp = temp->child[s[i]];
        }
        return temp->terminal;
    }
};