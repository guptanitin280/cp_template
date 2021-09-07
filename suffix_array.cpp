struct sufar{
    string s;
    vector<int>lcp,order,rank;
    int n;

    sufar(string _s){
        s=_s+"$";
        n=s.length();
    }

    void build(){
        order.resize(n);
        rank.resize(n);
        {
            vector<pair<int,int>>temp;
            for(int i=0;i<n;i++){
                temp.push_back({s[i]-'a',i});
            }
            sort(temp.begin(),temp.end());
            for(int i =0;i<n;i++){
                order[i]=temp[i].second;
            }
            rank[order[0]]=0;
            for(int i=1;i<n;i++){
                rank[order[i]]=rank[order[i-1]]+(temp[i].first!=temp[i-1].first);
            }
        }
        int k=0;
        vector<int>order_t(n,0),rank_t(n,0);
        while((1<<k)<n){
            for(int i =0;i<n;i++){
                (order[i]-=(1<<k)-n)%=n;
            }
            vector<int>cnt(n,0),pos(n,0);
            for(auto &c:rank)
                cnt[c]++;
            for(int i=1;i<n;i++)
                pos[i]=pos[i-1]+cnt[i-1];
            for(int i=0;i<n;i++)
                order_t[pos[rank[order[i]]]++]=order[i];
            order=order_t;
            for(int i=1;i<n;i++){
                pair<int,int>old_val={rank[order[i-1]],rank[(order[i-1]+(1<<k))%n]};
                pair<int,int>new_val={rank[order[i]],rank[(order[i]+(1<<k))%n]};
                rank_t[order[i]]=rank_t[order[i-1]]+(old_val!=new_val);
            }
            rank=rank_t;
            k++;
        }
    }
    void build_lcp(){
        lcp.resize(n,0);
        int k=0;
        for(int i=0;i<n-1;i++){
            int pos=rank[i];
            int j=order[pos-1];
            while(s[i+k]==s[j+k]) k++;
            lcp[pos]=k;
            k=max(k-1,(int)0);
        }
    }
    int occ_of_string(string &p){
        int m=p.length();
        int l=-1,r=n;
        while(l+1<r){
            int mid=(l+r)/2;
            if(s.substr(order[mid],m)<p){
                l=mid;
            }else{
                r=mid;
            }
        }
        int left=r;

        l=-1,r=n;
        while(l+1<r){
            int mid=(l+r)/2;
            if(s.substr(order[mid],m)<=p){
                l=mid;
            }else{
                r=mid;
            }
        }
        int right=l;

        int val=0;
        if(left<=right){
            val=right-left+1;
        }
        return val;
    }

    int different_substr(){
        build_lcp();
        int tot=(n*(n-1))/2;
        for(int i=1;i<n;i++) tot-=lcp[i];
        return tot;
    }
    
};
