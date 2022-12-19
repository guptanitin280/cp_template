int a[200001];
//for range min query and range update
struct node{
    //req variable
    int val;
    //default value
    node()
    {
        val=INT_MAX;
    }
};
class segte {
public:
    int n{};
    vector<node> tree;
    vector<int>lazy;
    vector<bool>prsnt;
    node neutral;

    void init(int N) {
        n = N;
        tree.resize(4 * n + 1);
        //default values
        lazy.assign(4*n+1,0);
        prsnt.assign(4*n+1,false);
    }

    //merge function
    static void merge(node &curr, node &left, node &right) {
        curr.val =min( left.val , right.val);
    }


    void prop(int index,int ss,int se)
    {
        tree[index].val+=lazy[index];
        if(ss!=se)
        {
            lazy[2*index]+=lazy[index];
            lazy[2*index+1]+=lazy[index];
            prsnt[2*index]=prsnt[2*index+1]=true;
        }
        lazy[index]=0;
        prsnt[index]=false;
    }

    void build(int index, int ss, int se) {
        if (ss == se) {
            tree[index].val=a[ss];
            return;
        }
        int mid = (ss + se) / 2;
        build(2 * index, ss, mid);
        build(2 * index + 1, mid + 1, se);
        merge(tree[index], tree[2 * index], tree[2 * index + 1]);
    }

    void build() {
        build(1, 0, n - 1);
    }

    node query(int index,int ss,int se,int qs,int qe)
    {
        if(prsnt[index])
            prop(index,ss,se);
        if (qs > se || qe < ss) return neutral;
        if (qs <= ss && qe >= se) return tree[index];
        int mid = (ss + se) / 2;
        node left = query(2 * index, ss, mid, qs, qe);
        node right = query(2 * index + 1, mid + 1, se, qs, qe);
        node mer;
        merge(mer, left, right);
        return mer;
    }
    node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    void update(int index, int ss, int se,int l,int r,int inc) {
        if (prsnt[index])
            prop(index, ss, se);
        if (r < ss || l > se)
            return;
        if (ss >= l && se <= r) {
            prsnt[index] = true;
            lazy[index] += inc;
            prop(index, ss, se);
            return;
        }
        int mid = (ss + se) / 2;
        update(2 * index, ss, mid, l, r, inc);
        update(2 * index + 1, mid + 1, se, l, r, inc);
        merge(tree[index], tree[2 * index], tree[2 * index + 1]);
    }
    void update(int l,int r,int inc) {
        update(1, 0, n - 1,l,r,inc);
    }
};