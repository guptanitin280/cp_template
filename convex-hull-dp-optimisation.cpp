struct line{
    int m;
    int c;
    line(int M,int C)
    {
        m=M;
        c=C;
    }
    int calc(int x)
    {
        return m*x+c;
    }

    double x_inter(line &l)
    {
        return (l.c-c)/((ld)(m-l.m));
    }
};
struct cht{
public:
    deque<pair<line,ld>>dq;
    void insert(line l)
    {
        if(dq.empty())
        {
            dq.pb({l,-1});
            return;
        }
        double x;
        while(!dq.empty())
        {
            x=l.x_inter(dq.back().f);
            if(x<=dq.back().s)
            {
                dq.pop_back();
            } else{
                break;
            }
        }
        dq.pb({l,x});
    }
    int query(int x)
    {
        while(sz(dq)>1)
        {
            if(dq[1].s<=x)
                dq.pop_front();
            else
                break;
        }
        return dq[0].f.calc(x);
    }
    //     int query_2(int x) { //when slope inc and query random //not tested yet
//         int lo = 0, hi = dq.size() ;
//         while (lo + 1 < hi) {
//             int mid = (lo + hi) / 2;
//             if (dq[mid-1].s<=x && dq[mid].s<=x) lo = mid;
//             else hi = mid;
//         }
//         return dq[lo].f.calc(x);
//     }
};