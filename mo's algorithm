struct query{
    int i,l,r,bno;
};

//basic comparator
bool cmp(query &a,query&b){
    if(a.bno!=b.bno){
        return a.bno<b.bno;
    }else{
        return a.r<b.r;
    }
}


int n,q,bs;
query qry[300001];
int a[300001];
int ans[300001];


int lp,rp,cnt;
int freq[1000001];

void add(int val){
    freq[val]++;
    if(freq[val]==1) cnt++;
}
void remove(int val){
    freq[val]--;
    if(freq[val]==0) cnt--;
}


void solve() {
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    bs=sqrt(n);
    cin>>q;

    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        --l;--r;
        qry[i].i=i;
        qry[i].l=l;
        qry[i].r=r;
        qry[i].bno=l/bs;
    }
    // sort the queries
    sort(qry,qry+q,cmp);

    // initialise the data-structure
    lp=0;
    rp=0;
    cnt=0;
    add(a[0]);

    // answer the queries
    for(int i=0;i<q;i++){
        int l=qry[i].l;
        int r=qry[i].r;

        while(rp<r){
            add(a[++rp]);
        }
        while(lp>l){
            add(a[--lp]);
        }

        while(rp>r){
            remove(a[rp--]);
        }
        while(lp<l){
            remove(a[lp++]);
        }

        ans[qry[i].i]=cnt;
    }

    for(int i=0;i<q;i++){
        cout<<ans[i]<<endl;
    }
}
