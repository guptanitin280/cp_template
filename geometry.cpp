#include <bits/stdc++.h>

typedef long double ld;
#define int long long

#define gcd            __gcd
//#define endl           "\n"
#define setbits(x)     __builtin_popcountll(x)
#define zrobits(x)     __builtin_ctzll(x)
#define mod            1000000007
#define mod2           998244353
#define maxe           *max_element
#define mine           *min_element
#define inf            1e18
#define pb             push_back
#define all(x)         x.begin(), x.end()
#define f              first
#define s              second
#define lb             lower_bound
#define ub             upper_bound
#define ins            insert
#define sz(x)          (int)(x).size()
#define mk             make_pair
#define deci(x, y)     fixed<<setprecision(y)<<x
#define w(t)           int t; cin>>t; while(t--)
#define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define PI             3.141592653589793238
#define mem0(x)        memset(x,0,sizeof x)
#define mem1(x)        memset(x,-1,sizeof x)
#define pr             pair<int,int>
#define vi             vector<int>
#define vvi            vector<vi>
#define vpr            vector<pr>
using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.f << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NITIN
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

struct point{
    int x,y,z;
    point(int _x=0,int _y=0,int _z=0){
        x=_x;
        y=_y;
        z=_z;
    }

    point operator+(point b) const{
        return {x+b.x,y+b.y,z+b.z};
    }

    point& operator+=(point b){
        return *this=*this+b;
    }

    point operator-(point b) const{
        return {x-b.x,y-b.y,z-b.z};
    }

    point& operator-=(point b){
        return (*this)=(*this)-b;
    }

    point operator*(int val) const{
        return {x*val,y*val,z*val};
    }

    point& operator*=(int val){
        return (*this)=(*this)*val;
    }

    point operator/(int val) const{
        return {x/val,y/val};
    }

    point& operator/=(int val){
        return (*this)=(*this)/val;
    }
    point& operator=(point b){
        x=b.x;
        y=b.y;
        z=b.z;
        return *this;
    }
    bool operator==(point b) const{
        return (x==b.x && y==b.y && z==b.z);
    }
    bool operator<(const point &a) const {
        if(a.x==x){
            return y<a.y;
        }else{
            return x<a.x;
        }
    }
    bool operator>(const point &a) const {
        if(a.x==x){
            return y>a.y;
        }else{
            return x>a.x;
        }
    }
};
int dot(point a , point b){
    return a.x*b.x+a.y*b.y;
}

point cross(point a , point b){
    return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x * b.y - a.y * b.x};
}

double angle(point a , point b){
    return acos(dot(a,b)/(sqrt(dot(a,a)*dot(b,b))));
}
bool check(int a,int b,int c,int d){
    if(a>b) swap(a,b);
    if(c>d) swap(c,d);
    return max(a,c)<=min(b,d);
}

int sgn(int x){
    if(x==0) return 0;
    if(x>0) return 1;
    return -1;
}
// for 2d only , z=0 , checks if two segments intersects or not
bool check_inter(point &a,point &b,point &c,point &d){
    if(cross(b-a,c-b)==0 && cross(b-a,d-b)==0){
        return check(a.x,b.x,c.x,d.x)&&check(a.y,b.y,c.y,d.y);
    }else{
        if(sgn(cross(b-a,c-b).z)==sgn(cross(b-a,d-b).z)) return false;
        if(sgn(cross(d-c,b-d).z) == sgn(cross(d-c,a-d).z)) return false;
        return true;
    }
}

int boundary_lp(point a,point b){
    return gcd(abs(a.x-b.x),abs(a.y-b.y))-1;
}


double dtr(double ang){
    return (ang*PI)/100;
}
double rtd(double ang){
    return (ang*180)/PI;
}

// sign of tot tells about if point given are in clockwise (neg) or anticlockwise (pos)
int area1(vector<point>v){
    int tot=0;
    int n=v.size();
    for(int i=0;i<v.size();i++){
        tot-=(v[(i+1)%n].x-v[i].x)*(v[(i+1)%n].y+v[i].y);
    }
    return abs(tot);
}
// 2*area
int area(vector<point>v){
    int tot=0;
    for(int i=0;i<sz(v)-1;i++){
        tot+=cross(v[i]-v[0],v[i+1]-v[0]).z;
    }
    return abs(tot);
}
// counterclockwise:>0, clockwise:<0, staright:0
int direction(point a,point b,point c){
    return sgn(cross(b-a,c-b).z);
}
//if point lie on segment
bool point_on_segment(point p,point a,point b){
    return direction(a,b,p)==0 && check(a.x,b.x,p.x,p.x) && check(a.y,b.y,p.y,p.y);
}
// 1 inside, 0 on the polygon,-1 outside convex polygon
// not yet tested
int point_in_cp(point &p,vector<point>&v){
    if(point_on_segment(p,v[0],v[1])){
        return 0;
    }
    if(point_on_segment(p,v[0],v[sz(v)-1])){
        return 0;
    }
    int l=1,r=sz(v);
    while(l+1<r){
        int m=(l+r)/2;
        if(direction(v[0],v[m],p)== direction(v[0],v[1],p)){
            l=m;
        }else{
            r=m;
        }
    }
    if(l==sz(v)-1){
        return -1;
    }
    if(point_on_segment(p,v[l],v[l+1])){
        return 0;
    }
    if(area1({v[0],v[l],v[l+1]})==area1({v[0],v[l],p})+area1({v[0],v[l+1],p})+area1({v[l],v[l+1],p})){
        return 1;
    }else{
        return -1;
    }
}
// lattice points in a polygon
pair<int,int> cnt_lp(vector<point>&p){
    int area2= area(p);
    int tot_bdry=0;
    int n=p.size();
    for(int i=0;i<p.size();i++){
        tot_bdry+= boundary_lp(p[i],p[(i+1)%n]);
    }
    tot_bdry+=sz(p);
    return {(area2-tot_bdry+2)/2,tot_bdry};
}
// reorder by first element being left bottom point
void reorder(vector<point>&a){
    int pos=0;
    for(int i=1;i<a.size();i++){
        if(a[i].x<a[pos].x || (a[i].x==a[pos].x && a[i].y<a[pos].y)){
            pos=i;
        }
    }
    rotate(a.begin(),a.begin()+pos,a.end());
}
vector<point> mink_sum(vector<point>a,vector<point>b){
    reorder(a);
    reorder(b);
    vector<point>ans;
    int i=0,j=0;
    int n=sz(a),m=sz(b);
    int times=n+m;
    while(times--){
        ans.push_back(a[i]+b[j]);
        if(cross(a[(i+1)%n]-a[i],b[(j+1)%m]-b[j]).z>=0){
            i++;
            i%=n;
        }else{
            j++;
            j%=m;
        }
    }
    // remove redundant points
    vector<point>r_ans;
    for(int l=0;l<n+m;l++){
        if(direction(ans[(l-1+n+m)%(n+m)],ans[l],ans[(l+1)%(n+m)])!=0){
            r_ans.push_back(ans[l]);
        }
    }
    return r_ans;
}
// angle sweep
int max_point_ic(vector<point>p,ld r){
    int n=p.size();
    int ans=1;
    for(int i=0;i<n;i++){
        vector<pair<ld,pair<bool,int>>>ang;
        int cur=1;
        for(int j=0;j<n;j++){
            if(i!=j){
                ld d=sqrt((ld)(dot(p[j]-p[i],p[j]-p[i])));
                if(d>2*r) continue;
                ld alpha1=atan((p[j]-p[i]).y/((ld)(p[j]-p[i]).x));
                if((p[j]-p[i]).x<0) alpha1+=PI;
                ld alpha2=acos(d/(2*r));
                ld entry=(8*PI+alpha1-alpha2);
                entry-=2*PI* floor(entry/(2*PI));
                ld exit=(8*PI+alpha1+alpha2);
                exit-=2*PI* floor(exit/(2*PI));
                if(entry>exit) cur++;
                ang.push_back({entry,{false,j}});
                ang.push_back({exit,{true,j}});
            }
        }
        sort(ang.begin(),ang.end());
        ans=max(ans,cur);
        for(auto &c:ang){
            if(!c.second.first) cur++;
            else cur--;
            ans=max(ans,cur);
        }
    }
    return ans;
}

// line sweep
int min_ed(vector<point>&v){
    priority_queue<point,vector<point>,greater<>>pq;
    set<point>s;
    int dist=8e18;
    sort(v.begin(),v.end());
    for(auto &c:v){
        int d=ceil(sqrt(dist));
        while(!pq.empty() && pq.top().x<=c.x-d){
            s.erase(point(pq.top().y,pq.top().x));
            pq.pop();
        }
        auto it=s.lower_bound({c.y-d,INT_MIN});
        while(it!=s.end() && it->x<c.y+d){
            dist=min(dist,(it->x-c.y)*(it->x-c.y)+(it->y-c.x)*(it->y-c.x));
            it=next(it);
        }
        pq.push(c);
        s.insert(point(c.y,c.x));
    }
    return dist;
}
//convex hull:jarvis march (return convex hull giving anticlockwise point with bottom left as first point
// doesnt include collinear point
vector<point> convex_hull_jm(vector<point>a){
    int n=a.size();

    int idx=0;
    for(int j=1;j<n;j++){
        if(a[j].x<a[idx].x || (a[j].x==a[idx].x && a[j].y<a[idx].y)){
            idx=j;
        }
    }

    vector<point>hull;
    hull.push_back(a[idx]);
    while(true){
        point candidate=a[0];
        for(int i=0;i<n;i++){
            if(a[i]==hull.back()) continue;
            if(direction(hull.back(),candidate,a[i])==-1 || (
                    direction(hull.back(),candidate,a[i])==0 &&
                    dot(a[i]-hull.back(),a[i]-hull.back())>dot(candidate-hull.back(),candidate-hull.back())))
            {
                candidate=a[i];
            }
        }
        if(candidate==hull.front()) break;
        else hull.push_back(candidate);
    }
    return hull;
}
// convex hull: graham scan
point pin;
bool cmp(point a,point b){
    int d= direction(pin,a,b);
    if(d==-1) return false;
    else if(d==1) return true;
    else return dot(pin-a,pin-a)<dot(pin-b,pin-b);
}
vector<point> convex_hull_gc(vector<point>a){
    if(a.size()<=2) return a;
    int n=a.size();
    for(int i=1;i<n;i++){
        if(a[i].x<a[0].x || (a[i].x==a[0].x && a[i].y<a[0].y)){
            swap(a[0],a[i]);
        }
    }
    pin=a[0];
    sort(a.begin()+1,a.end(),cmp);
    vector<point>stk;
    stk.push_back(a[0]);
    stk.push_back(a[1]);
    for(int i=2;i<n;i++){
        while(stk.size()>=2 && direction(stk[sz(stk)-2],stk[sz(stk)-1],a[i])<=0){
            stk.pop_back();
        }
        stk.push_back(a[i]);
    }
    // to include redundant point also and change condition to <0 in while loop
    //    for(int i=n-2;i>0;i--){
    //        if(direction(a[0],a[i],a.back())==0){
    //            stk.push_back(a[i]);
    //        }
    //    }
    return stk;
}
// rotating calliper:- largest euclid distance, diameter of convex polygon
// return a^2
int diameter(vector<point>a){
    a= convex_hull_gc(a);
    int n=a.size();
    int ptr_a=0;
    int ptr_b=1;
    while(cross(a[(ptr_a+1)%n]-a[ptr_a],a[(ptr_b+1)%n]-a[ptr_b])>0){
        ptr_b++;
        ptr_b%=n;
    }
    int ans=dot(a[ptr_b]-a[ptr_a],a[ptr_b]-a[ptr_a]);
    int begin_a=ptr_a;
    int begin_b=ptr_b;
    do{
        if(cross(a[(ptr_a+1)%n]-a[ptr_a],a[(ptr_b+1)%n]-a[ptr_b])>0){
            ptr_b++;
            ptr_b%=n;
        }else{
            ptr_a++;
            ptr_a%=n;
        }
        ans=max(ans,dot(a[ptr_b]-a[ptr_a],a[ptr_b]-a[ptr_a]));
    }while(begin_a!=ptr_a || begin_b!=ptr_b);
    return ans;
}

void solve() {
    int n;
    cin>>n;
    vector<point>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].x>>v[i].y;
    }
    cout<<diameter(v)<<endl;
}


int32_t main() {
    nitin;
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case #"<<i<<endl;
        solve();
    }
}
