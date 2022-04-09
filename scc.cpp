// strongly connected component
// https://atcoder.jp/contests/abc245/tasks/abc245_f

vector<int>v[200001]; // given graph
vector<int>rv[200001]; // reverse graph
set<int>ng[200001]; // new component graph
stack<int>stk;
bool vis[200001];
int compNo[200001]; //  component number
vector<vector<int>>strongly_components;

void dfs(int node) {
    vis[node] = true;
    for (auto &c: v[node]) {
        if (!vis[c]) {
            dfs(c);
        }
    }
    stk.push(node);
}
void rdfs(int node,vector<int>&comp) {
    vis[node] = true;
    comp.push_back(node);
    for (auto &c: rv[node]) {
        if (!vis[c]) {
            rdfs(c, comp);
        }
    }
}

bool infi[200001];
void tdfs(int node){
    vis[node]=true;
    for(auto &c:ng[node]){
        if(!vis[c]){
            tdfs(c);
        }
        infi[node]|=infi[c];
    }
}


void solve() {
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        v[a].push_back(b);
        rv[b].push_back(a);
    }
    for(int i=0;i<n;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    memset(vis,false,sizeof vis);
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();
        if (vis[node]) continue;
        vector<int> component;
        rdfs(node, component);
        for(auto &c:component){
            compNo[c]=strongly_components.size();
        }
        if(component.size()>1){
            infi[strongly_components.size()]=true;
        }
        strongly_components.push_back(component);
    }
    for(int i=0;i<n;i++){
        for(auto &c:v[i]){
            if(compNo[i]!=compNo[c]){
                ng[compNo[i]].insert(compNo[c]);
            }
        }
    }

    /*************************************************************************************/
    memset(vis,false,sizeof vis);
    for(int i=0;i<n;i++){
        if(!vis[compNo[i]]){
            tdfs(compNo[i]);
        }
    }
    dbg(strongly_components);
    int cnt=n;
    for(int i=0;i<strongly_components.size();i++){
        if(!infi[i]){
            cnt--;
        }
    }
    cout<<cnt<<endl;
}

int32_t main() {
    nitin;

    solve();
}
