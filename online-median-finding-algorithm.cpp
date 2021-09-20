/*
 online median finding algorithm (make two multiset first one for <=median and other one for >median
                                           now just maintain size(a)==size(b) or size(a)==size(b)+1
                                               */
//S.size()==T.size()  or  S.size()==T.size()+1
struct med{
    multiset<int>a,b;
    void crct(){
        int n=a.size()+b.size();
        while(a.size()<b.size()+(n&1)){
            a.insert(*b.begin());
            b.erase(b.begin());
        }
        while(b.size()+(n&1)<a.size()){
            b.insert(*prev(a.end()));
            a.erase(prev(a.end()));
        }
    }
    void erase(int x){
        if(a.count(x)) a.erase(a.find(x));
        else if(b.count(x)) b.erase(b.find(x));
        crct();
    }
    void insert(int x){
        if(a.empty() || b.empty())
            a.insert(x);
        else if(x<=*b.begin()) a.insert(x);
        else b.insert(x);
        crct();
    }
    int val(){
        int n=a.size()+b.size();
        if(n&1) return *(prev(a.end()));
        else return (*(prev(a.end()))+(*b.begin()))/2;
    }
};



