const int N=200001;
vector<int>ord;
int tin[N],tout[N];
int tme=-1;
vector<int>v[N];

// for subtree queries
// for x, subtree of x is subarray in array ord from [tin[x],tout[x]]
void eut_1(int node,int p){
    tin[node]=++tme;
    ord.push_back(node);
    for(auto &c:v[node]){
        if(c!=p){
            eut_1(c,node);
        }
    }
    tout[node]=tme;
}

// for path queries
// for x, subtree of x is subarray in array ord from [tin[x],tout[x]] but twice
// for path u->v, and u is ancestor to v then the subarray [tin[u],tin[v]] has single occurrence for the ancestors of v
// which lie on the path and every other node have double occurrence ( single occurrences is of opening type only )
// for path u->v, tout[u]<tin[v],subarray [tout[u],tin[v]] contain single occurrence for path node ( except lca) and double
// occurrence for non path node ( single occurrences if of both opening type and closing type )
void eut_2(int node,int p){
    tin[node]=++tme;
    ord.push_back(node);
    for(auto &c:v[node]){
        if(c!=p){
            eut_2(c,node);
        }
    }
    tout[node]=++tme;
    ord.push_back(node);
}
// for O(1) lca queries
// lca of u,v is the min of lvl[ord[x]] in st[u]<=x<=st[v]
// subtree of x occur from [tin[x],tout[x]] but with multiple occurrences
// every edge occur twice so can be used for edge queries and updates
// ord.length:- 2*edges+1
int lvl[N];
void eut_3(int node,int p){
    tin[node]=++tme;
    ord.push_back(node);
    for(auto &c:v[node]){
        if(c!=p){
            lvl[c]=lvl[node]+1;
            eut_3(c,node);
            ++tme;
            ord.push_back(node);
        }
    }
    tout[node]=tme;
}
