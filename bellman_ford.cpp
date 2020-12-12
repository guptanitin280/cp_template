vector<pair<int,int>>v[200001];
int dist[200001];
bool neg_cycle=false;
int n,m;
void bellman_ford(int source) {
    for (int i = 0; i < n; i++) dist[i] = INT_MAX;
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            for (auto c:v[j]) {
                if (dist[j] != INT_MAX && dist[c.f] > dist[j] + c.s) {
                    dist[c.f] = dist[j] + c.s;
                }
            }
        }
    }
//    for(int i=0;i<n;i++)
//    {
//        for(auto c:v[i])
//        {
//            if(dist[j]!=INT_MAX && dist[c.f]>dist[j]+c.s)
//            {
//                neg_cycle=true;
//                break;
//            }
//        }
//    }

}