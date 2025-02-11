#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n, m;
vector<int> g[200010];
int v[200010];
int dt[200010];
int low[200010];

// found articulation points
// can be replaced with vector, but duplicates must be removed
set<int> res;

int curt = 1;

void adfs(int s, int p) {
    if (v[s]) return;
    v[s] = 1;
    dt[s] = curt++;
    low[s] = dt[s];
    
    int ccount = 0;
    
    for (int a : g[s]) {
        if (!v[a]) {
            ++ccount;
            adfs(a, s);
            low[s] = min(low[s], low[a]);
            
            if (low[a] >= dt[s] && p != -1) res.insert(s);
        }
        else if (a != p) {
            low[s] = min(low[s], dt[a]);
        }
        
        if (p == -1 && ccount > 1) {
            res.insert(s);
        }
    }
}


int main() {
    for (int i = 1; i <= n; ++i) {
        if (!v[i]) adfs(i, -1);
    }
}
