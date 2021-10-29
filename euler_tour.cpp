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
