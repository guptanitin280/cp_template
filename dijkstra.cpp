vector<pair<int,int>>v[200001];
int dist[200001];
int n,m;
void dijkstra(int source)
{
    for(int i=0;i<n;i++)
        dist[i]=INT_MAX;
    dist[source]=0;
    set<pair<int,int>>s;
    s.insert({0,source});
    while(!s.empty())
    {
        int vert=s.begin()->second;
        s.erase(s.begin());
        for(auto c:v[vert])
        {
            if(dist[c.f]>dist[vert]+c.s)
            {
                if(s.count({dist[c.f],c.f}))
                    s.erase({dist[c.f],c.f});
                dist[c.f]=dist[vert]+c.s;
                s.insert({dist[c.f],c.f});
            }
        }
    }
}