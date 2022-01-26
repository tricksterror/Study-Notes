// binary search is a search algorithm that applies on a monotonic fucntions

//upper bound and lower bound implementations

#include <bits/stdc++.h>
using namespace std;

int upper_bound(vector<int> &v, int element) {
        int l = 0, h = v.size()-1;
        while (h - l > 1) {
                int mid = (l + h) >> 1;
                if (v[mid] > element) h = mid;
                else l = mid + 1;
        }
        if (v[l] > element) return l;
        if (v[h] > element) return h;
        return -1;
}

int lower_bound(vector<int> &v, int element) {
        int l = 0, h = v.size()-1;
        while (h - l > 1) {
                int mid = (l + h) >> 1;
                if (v[mid] >= element) h = mid;
                else l = mid + 1;
        }
        if (v[l] >= element) return l;
        if (v[h] >= element) return h;
        return -1;
}

signed main()
{
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        int n;
        cin >> n;
        vector<int> v(n);
        for (int &x : v) {
                cin >> x;
        }
        int element;
        cin >> element;
        int lb = lower_bound(v, element);
        cout << lb << "-->" << (lb != -1? v[lb]: -1) << "\n";
        int ub = upper_bound(v, element);
        cout << ub << "-->" << (ub != -1? v[ub]: -1) << "\n";
        return 0;
}

//calculating nth root using binary search

#include <bits/stdc++.h>
using namespace std;

double eps = 1e-7;

signed main()
{
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        double x;
        cin >> x;
        int n;
        cin >> n;
        double l = 1, h = x, mid;
        while (h - l > eps) {
                mid = (l + h)/2;
                double ans = 1.0;
                for (int i = 0; i < n; i++) {
                        ans *= mid;
                }
                if (ans < x) l = mid;
                else h = mid;
        }
        cout << setprecision(10) << h << "\n"<< l << "\n";
        cout << setprecision(10) << pow(x, 1.0/n) << "\n";
        return 0;
}


// EKO problem lumberjack https://www.spoj.com/problems/EKO/
// time complexity N*log(h)

#include <bits/stdc++.h>
using namespace std;
#define int long long int

const int N = 1e6+10;

int n, m, trees[N];

bool iswoodsuff(int h) {
        int wood = 0;
        for (int i = 0; i < n; i++) {
                if (trees[i] >= h) wood += (trees[i]-h);
        }
        return wood >= m;
}

signed main()
{
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
                cin >> trees[i];
        }
        int l = 0, h = 1e9, mid;
        while (h - l > 1) {
                mid = (h + l) >> 1;
                if (iswoodsuff(mid)) l = mid;
                else h = mid-1;
        }
        int ans = l;
        if (iswoodsuff(h)) ans = h;
        cout << ans << "\n";
        return 0;
}

//tle code of aggresive cows

#include <bits/stdc++.h>
using namespace std;
#define int long long int

const int N = 1e5+10;
int n, cows, pos[N];

bool canplace(int x) {
        int lastpos = -1, cows_cnt = cows;
        for (int i = 0; i < n; i++) {
                if (pos[i] - lastpos >= x || lastpos == -1) {
                        cows_cnt--;
                        lastpos = pos[i];
                }
                if (cows_cnt == 0) break;
        }
        return cows_cnt == 0;
}

void solve() {
        cin >> n >> cows;
        for (int i = 0; i < n; i++) {
                cin >> pos[i];
        }
        sort(pos, pos+n);
        int l = 0, h = 1e9, mid;
        while (h - l > 1) {
                mid = (h + l) >> 2;
                int lastpos = -1, cows_cnt = cows;
                for (int i = 0; i < n; i++) {
                        if (pos[i] - lastpos >= mid || lastpos == -1) {
                                cows_cnt--;
                                lastpos = pos[i];
                        }
                        if (cows_cnt == 0) break;
                }
                if (cows_cnt == 0) l = mid;
                else h = mid - 1;
        }
        int ans = l;
        if (canplace(h)) ans = h;
        cout << ans << "\n";
}

signed main()
{
        ios::sync_with_stdio(false); 
        cin.tie(nullptr);
        #ifndef ONLINE_JUDGE
        freopen("inputf.in", "r", stdin);
        #endif
        
        int _;
        cin >> _;
        for (_; _; _--) {
                solve();
        }
        return 0;
}

// cellular network(binary search with two pointer) https://codeforces.com/contest/702/problem/C 
