struct point{
    int x,y;


};
bool operator < (const point &q,const point &p)
{
    if(p.x==q.x) return q.y<p.y;
    else return q.x<p.x;
}
bool operator ==(const point &a,const point &b)
{
    return a.x==b.x && b.y==a.y;
}

bool c_w(point a,point b,point c)
{
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) >0;
}
bool ac_w(point a,point b,point c)
{
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) <0;
}
bool coll(point a,point b,point c)
{
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) ==0;
}
vector<point>hull;
void convex_hull(vector<point>&p) {
    if (p.size() <= 2) return;
    sort(p.begin(), p.end());
    int n = p.size();
    vector<point> up, down;
    up.pb(p[0]);
    down.pb(p[0]);

    point p1 = p[0]; //bottom left
    point p2 = p[n - 1]; // top right
    for (int i = 1; i < n; i++) {
        if (!ac_w(p1, p[i], p2)) {
            //upper half with collinear case
            while (up.size() >= 2 && ac_w(up[up.size() - 2], up[up.size() - 1], p[i])) {
                up.pop_back();
            }
            up.pb(p[i]);
        }
        if (!c_w(p1, p[i], p2)) {
            //bottom half with collinear case
            while (down.size() >= 2 && c_w(down[down.size() - 2], down[down.size() - 1], p[i])) {
                down.pop_back();
            }
            down.pb(p[i]);
        }
    }
    for (auto c:up) {
        hull.push_back(c);
    }
    for (auto c:down) {
        hull.push_back(c);
    }
    sort(hull.begin(), hull.end());
    hull.resize(unique(all(hull)) - hull.begin());
}