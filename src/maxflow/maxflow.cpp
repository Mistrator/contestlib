#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 105; // vertex count
const ll LINF = 1000000000000000005;

int n, m;
vector<int> g[N];
ll d[N][N]; // edge weights

int v[N];
vector<int> cp; // current augmenting path

ll res = 0;

// find augmenting path using scaling
// prerequisities: clear current path, divide threshold by 2, increment cvis
ll dfs(int s, int t, ll thresh, int cvis, ll cmin) {
    if (v[s] == cvis) return -1;
    v[s] = cvis;
    cp.push_back(s);   
    if (s == t) return cmin;
    
    for (int a : g[s]) {
        if (d[s][a] < thresh) continue; // scaling
        ll cres = dfs(a, t, thresh, cvis, min(cmin, d[s][a]));
        if (cres != -1) return cres;
    }
    
    cp.pop_back();
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    ll cthresh = 0;
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g[a].push_back(b);
        g[b].push_back(a);
        d[a][b] += c;
        d[b][a] = 0;
        cthresh += c;
    }
    int cvis = 0;
    while (true) {
        cvis++;
        cp.clear();
        ll minw = dfs(1, n, cthresh, cvis, LINF);
        if (minw != -1) {
            res += minw;
            for (int i = 0; i < cp.size()-1; ++i) {
                d[cp[i]][cp[i+1]] -= minw;
                d[cp[i+1]][cp[i]] += minw;
            }
        }
        else {
            if (cthresh == 1) break;
            cthresh /= 2;
        }
    }
    cout << res << "\n";
    return 0;
}
