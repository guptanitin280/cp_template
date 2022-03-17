// https://cses.fi/problemset/task/2084/
// cht-(general in query, not in insertion)
struct line {
    int m, c;

    line(int _m, int _c) : m(_m), c(_c) {
    }

    ld intersection(line l) {
        ld top = l.c - c;
        ld bottom = m - l.m;
        return top / bottom;
    }

    int get_val(int x) {
        return m * x + c;
    }
};

// to get minimum value
// slope of line added is in decreasing order
// query asked is in increasing order/ random order
struct cht {
    deque<pair<line, ld>> dq;

    void insert(line l) {
        if (!dq.empty() && dq.back().first.m == l.m) {
            if (dq.back().first.c <= l.c) return;
            dq.pop_back();
        }
        while (!dq.empty()) {
            ld x1 = dq.back().first.intersection(l);
            ld x2 = dq.back().second;
            if (x2 >= x1) {
                dq.pop_back();
            } else {
                break;
            }
        }
        if (dq.empty())
            dq.push_back({l, -1});
        else
            dq.push_back({l, l.intersection(dq.back().first)});
    }
    // query asked in increasing order
    int query(int x) {
        while (dq.size() > 1 && dq[0].first.get_val(x) >= dq[1].first.get_val(x))
            dq.pop_front();
        return dq[0].first.get_val(x);
    }

    // query general
    int queryG(int x) {
        int l = 0, r = sz(dq);
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (dq[m].second <= x) {
                l = m;
            } else {
                r = m;
            }
        }
        return dq[l].first.get_val(x);
    }
};















// struct line{
//     int m;
//     int c;
//     line(int M,int C)
//     {
//         m=M;
//         c=C;
//     }
//     int calc(int x)
//     {
//         return m*x+c;
//     }

//     double x_inter(line &l)
//     {
//         return (l.c-c)/((ld)(m-l.m));
//     }
// };
// struct cht{
// public:
//     deque<pair<line,ld>>dq;
//     void insert(line l)
//     {
//         if(dq.empty())
//         {
//             dq.pb({l,-1});
//             return;
//         }
//         double x;
//         while(!dq.empty())
//         {
//             x=l.x_inter(dq.back().f);
//             if(x<=dq.back().s)
//             {
//                 dq.pop_back();
//             } else{
//                 break;
//             }
//         }
//         dq.pb({l,x});
//     }
//     int query(int x)
//     {
//         while(sz(dq)>1)
//         {
//             if(dq[1].s<=x)
//                 dq.pop_front();
//             else
//                 break;
//         }
//         return dq[0].f.calc(x);
//     }
    //     int query_2(int x) { //when slope inc and query random //not tested yet
//         int lo = 0, hi = dq.size() ;
//         while (lo + 1 < hi) {
//             int mid = (lo + hi) / 2;
//             if (dq[mid-1].s<=x && dq[mid].s<=x) lo = mid;
//             else hi = mid;
//         }
//         return dq[lo].f.calc(x);
//     }
// };
