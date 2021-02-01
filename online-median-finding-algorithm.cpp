/*
 online median finding algorithm (make two multiset first one for <=median and other one for >median
                                           now just maintain size(a)==size(b) or size(a)==size(b)+1
                                               */
            int median=inf;
            multiset<int>a,b;
            if(x<=median){
                a.ins(x);
            }
            else{
                b.ins(x);
            }
            if(a.size()>b.size()+1){
                int ele=*prev(a.end());
                b.ins(ele);
                a.erase(a.find(ele));
            }
            else if(b.size()>=a.size()+1) {
                int ele = *b.begin();
                a.ins(ele);
                b.erase(b.find(ele));
            }
            median=*prev(a.end());



