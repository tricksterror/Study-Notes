//basic structure of a dfs program.

void dfs(int vertex) {
        //take action on vertex after entering the vertex
        //here before and after means before and after executing the dfs
        //section of going up
        vis[vertex] = true;
        for (int child : g[vertex]) {
                //take action on child before entering the child
                //section of going up
                if (vis[child]) continue;
                dfs(child);
                //take action on child after exiting the child node
                //section of going down
       }
       // take action on vertex before exiting the vertex
       //section of going down
}

//finding total no of connected components

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3+10;
vector<int> g[N];
vector<bool> vis(N, false);

void dfs(int vertex) {
        vis[vertex] = true;
        for (int child : g[vertex]) {
                if (vis[child]) continue;
                dfs(child);
       }
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(NULL); cout.tie(NULL);

        int n,m;
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
                int v1, v2; cin >> v1 >> v2;
                g[v1].push_back(v2); g[v2].push_back(v1);
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
                if(vis[i]) continue;
                dfs(i); cnt++;
        }
        cout << cnt << "\n";
        return 0;
}


//storing connected components in a vector

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3+10;
vector<int> g[N];
vector<bool> vis(N, false);

vector<vector<int>> cc;
vector<int> current_cc;

void dfs(int vertex) {
        vis[vertex] = true;
        current_cc.push_back(vertex);
        for (int child : g[vertex]) {
                if (vis[child]) continue;
                dfs(child);
       }
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(NULL); cout.tie(NULL);

        int n,m;
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
                int v1, v2; cin >> v1 >> v2;
                g[v1].push_back(v2); g[v2].push_back(v1);
        }
        for (int i = 1; i <= n; i++) {
                if(vis[i]) continue;
                current_cc.clear();
                dfs(i); cc.push_back(current_cc);
        }
        cout << cc.size() << "\n";
        for (auto x : cc) {
                for (int y : x) cout << y << ", ";
                cout << "\n";
        }
        return 0;
}

//finding cycles in graph


#include <bits/stdc++.h>
using namespace std;

const int N = 1e3+10;
vector<int> g[N];
vector<bool> vis(N, false);

bool dfs(int vertex, int par) {
        bool loop_ok = false;
        vis[vertex] = true;
        for (int child : g[vertex]) {
                if (vis[child] && child == par) continue;
                if (vis[child]) return true;
                loop_ok |= dfs(child, vertex);
       }
       return loop_ok;
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(NULL); cout.tie(NULL);

        int n,m;
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
                int v1, v2; cin >> v1 >> v2;
                g[v1].push_back(v2); g[v2].push_back(v1);
        }
        bool isloop = false;
        for (int i = 1; i <= n; i++) {
                if (vis[i]) continue;
                if(dfs(i,0)) {
                        isloop = true; break;
                }
        }
        cout << isloop << "\n";
        return 0;
}

//calculation of depth and height
//depth is calculated while coming down in dfs and height is calculated while moving up in dfs

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> g[N];
int depth[N], height[N];

void dfs(int vertex, int par = 0) {
        for (int child : g[vertex]) {
                if (child == par) continue;
                depth[child] = depth[par] + 1;
                dfs(child, vertex);
                height[vertex] = max(height[vertex], height[child] + 1);
       }
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(NULL); cout.tie(NULL);

        int n;
        cin >> n;
        for (int i = 0; i < n-1; ++i) {
                int v1, v2; cin >> v1 >> v2;
                g[v1].push_back(v2); g[v2].push_back(v1);
        }
        dfs(1);
        for (int i = 1; i <= n; i++) {
                cout << depth[i] << " " << height[i] << "\n";
        }
        return 0;
}

//precomputation using dfs of even count and subtree sum

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> g[N];
vector<int> subtree_sum(N, 0);
vector<int> even_cnt(N);

void dfs(int vertex, int par = 0) {
        if (vertex%2 == 0) even_cnt[vertex]++;
        subtree_sum[vertex] += vertex;
        for (int child : g[vertex]) {
                if (child == par) continue;
                dfs(child, vertex);
                subtree_sum[vertex] += subtree_sum[child];
                even_cnt[vertex] += even_cnt[child];
       }
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(nullptr); cout.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        int n;
        cin >> n;
        for (int i = 0; i < n-1; ++i) {
                int v1, v2; 
                cin >> v1 >> v2;
                g[v1].push_back(v2); 
                g[v2].push_back(v1);
        }
        dfs(1);
        for (int i = 1; i < n+1; i++) {
                cout << subtree_sum[i] << " " << even_cnt[i] << "\n";
        }
        // int q;
        // cin >> q;
        // while (q--) {
        //         int v;
        //         cin >> v;
        //         cout << subtree_sum[v] << " " << even_cnt[v] << "\n";
        // }
        return 0;
}


// finding the diameter of tree

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> g[N];

vector<int> depth(N);

void dfs(int vertex, int par = 0) {
        for (int child : g[vertex]) {
                if (child == par) continue;
                depth[child] = depth[vertex] + 1;
                dfs(child, vertex);
        }
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(nullptr); cout.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        int n;
        cin >> n;
        for (int i = 0; i < n-1; ++i) {
                int v1, v2; 
                cin >> v1 >> v2;
                g[v1].push_back(v2); 
                g[v2].push_back(v1);
        }
        dfs(1);
        int mx_depth = -1, mx_node;
        for (int i = 1; i <= n; i++) {
                if (mx_depth < depth[i]) {
                        mx_depth = depth[i];
                        mx_node = i;
                }
                depth[i] = 0;
        }
        dfs(mx_node);
        mx_depth = -1;
        for (int i = 1; i <= n; i++) {
                if (mx_depth < depth[i]) mx_depth = depth[i];
        }
        cout << mx_depth << "\n";
        return 0;
}

// finding the LCA(lowest common ancestor)

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> g[N], par(N);

void dfs(int vertex, int p = 0) {
        par[vertex] = p;
        for (int child : g[vertex]) {
                if (child == p) continue;
                dfs(child, vertex);
        }
}

vector<int> path(int v) {
        vector<int> a;
        while (v != 0) {
                a.push_back(v);
                v = par[v];
        }
        reverse(a.begin(), a.end());
        return a;
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(nullptr); cout.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        int n;
        cin >> n;
        for (int i = 0; i < n-1; ++i) {
                int v1, v2; 
                cin >> v1 >> v2;
                g[v1].push_back(v2); 
                g[v2].push_back(v1);
        }
        dfs(1);
        int x, y;
        cin >> x >> y;
        vector<int> path_x = path(x);
        vector<int> path_y = path(y);
        int mn = min(path_x.size(), path_y.size());

        int lca = -1;
        for (int j = 0; j < mn; j++) {
                if (path_x[j] == path_y[j]) lca = path_x[j];
                else break;
        }
        cout << lca << "\n";
        return 0;
}

// edge deletion questions 

#include <bits/stdc++.h>
using namespace std;
#define int long long int

const int N = 1e5+10, M = 1e9+7;

vector<int> g[N], subtree_sum(N), val(N);

void dfs(int vertex, int p = 0) {
        subtree_sum[vertex] += val[vertex];
        for (int child : g[vertex]) {
                if (child == p) continue;
                dfs(child, vertex);
                subtree_sum[vertex] += subtree_sum[child];
        }
}

signed main()
{
        std::ios_base::sync_with_stdio(NULL);
        cin.tie(nullptr); cout.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        int n;
        cin >> n;
        for (int i = 0; i < n-1; ++i) {
                int v1, v2; 
                cin >> v1 >> v2;
                g[v1].push_back(v2); 
                g[v2].push_back(v1);
        }
        dfs(1);
        int ans = 0;
        for (int i = 2; i <= n; i++) {
                int part1 = subtree_sum[i];
                int part2 = subtree_sum[1] - part1;
                ans = (part1*part2)%M;
        }
        cout << ans << "\n";
        return 0;
}
