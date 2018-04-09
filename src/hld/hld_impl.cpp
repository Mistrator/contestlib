#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

const int S = 100005; // vertex count
const int N = (1<<18); // segtree size, must be >= S

vector<int> g[S];

int sz[S], de[S], pa[S];
int cind[S], chead[S], cpos[S];
int cchain, cstind, stind[S];

// IMPLEMENT SEGMENT TREE HERE
// st_update() and st_query() should call segtree functions
ll st[2*N]; // segtree values
ll lz[2*N]; // lazy updates
bool haslz[2*N]; // does a node have a lazy update pending

void push(int s, int l, int r) {
    if (haslz[s]) {
        st[s] += (r-l+1)*lz[s]; // change operator+logic

        if (l != r) {
            lz[2*s] += lz[s]; // change operator
            lz[2*s+1] += lz[s]; // change operator
            haslz[2*s] = true;
            haslz[2*s+1] = true;
        }

        lz[s] = 0; // set to identity
        haslz[s] = false;
    }
}

ll kysy(int ql, int qr, int s = 1, int l = 0, int r = N-1) {
    push(s, l, r);
    if (l > qr || r < ql) {
        return 0; // set to identity
    }
    if (ql <= l && r <= qr) {
        return st[s];
    }

    int mid = (l+r)/2;
    ll res = 0; // set to identity
    res += kysy(ql, qr, 2*s, l, mid); // change operator
    res += kysy(ql, qr, 2*s+1, mid+1, r); // change operator
    return res;
}

void muuta(int ql, int qr, ll x, int s = 1, int l = 0, int r = N-1) {
    push(s, l, r);
    if (l > qr || r < ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        lz[s] += x; // change operator
        haslz[s] = true;
        return;
    }

    int mid = (l+r)/2;
    muuta(ql, qr, x, 2*s, l, mid);
    muuta(ql, qr, x, 2*s+1, mid+1, r);

    st[s] = st[2*s] + st[2*s+1]; // change operator
    if (haslz[2*s]) {
        st[s] += (mid-l+1)*lz[2*s]; // change operator+logic
    }
    if (haslz[2*s+1]) {
        st[s] += (r-(mid+1)+1)*lz[2*s+1]; // change operator+logic
    }
}

void hdfs(int s, int p, int cd) {
    de[s] = cd;
    pa[s] = p;
    sz[s] = 1;
    for (int a : g[s]) {
        if (a == p) continue;
        hdfs(a, s, cd+1);
        sz[s] += sz[a];
    }
}

void hld(int s) {
    if (chead[cchain] == 0) {
        chead[cchain] = s;
        cpos[s] = 0;
    }
    else {
    	cpos[s] = cpos[pa[s]]+1;
    }
    cind[s] = cchain;

    stind[s] = cstind;
    cstind++;
    
    int cmx = 0, cmi = -1;
    for (int i = 0; i < g[s].size(); ++i) {
        if (g[s][i] == pa[s]) continue;
        if (sz[g[s][i]] > cmx) {
            sz[g[s][i]] = cmx;
            cmi = i;
        }
    }
    
    if (cmi != -1) {
        hld(g[s][cmi]);
    }
    
    for (int i = 0; i < g[s].size(); ++i) {
        if (i == cmi) continue;
        if (g[s][i] == pa[s]) continue;
        cchain++;
        cstind++;
        hld(g[s][i]);
    }
}

// do a range update on underlying segtree
// sa and sb are segtree indices
void st_update(int sa, int sb, ll x) {
    muuta(sa, sb, x);
}

// do a range query on underlying segtree
// sa and sb are segtree indices
ll st_query(int sa, int sb) {
    return kysy(sa, sb);
}

// update all vertices on path from vertex a to b
// a and b are vertex numbers
void path_update(int a, int b, ll x) {
    while (cind[a] != cind[b]) {
        if (de[chead[cind[b]]] > de[chead[cind[a]]]) swap(a, b);
        st_update(stind[chead[cind[a]]], stind[a], x);
        a = pa[chead[cind[a]]];
    }
    if (stind[b] < stind[a]) swap(a, b);
    st_update(stind[a], stind[b], x);
}

// query all vertices on path from vertex a to b
// a and b are vertex numbers
ll path_query(int a, int b) {
	ll cres = 0; // set to identity
	while (cind[a] != cind[b]) {
        if (de[chead[cind[b]]] > de[chead[cind[a]]]) swap(a, b);
        cres += st_query(stind[chead[cind[a]]], stind[a]); // change operator
        a = pa[chead[cind[a]]];
    }
    if (stind[b] < stind[a]) swap(a, b);
    cres += st_query(stind[a], stind[b]); // change operator
    return cres;
}


int n, m;

// do updates and queries on paths between two nodes in a tree
// interface: path_update() and path_query()
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // init hld
    hdfs(1, -1, 0);
    hld(1);

    // handle queries
    for (int i = 0; i < m; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int a, b;
            cin >> a >> b;
            cout << path_query(a, b) << "\n";
        }
        else {
            int a, b, x;
            cin >> a >> b >> x;
            path_update(a, b, x);
        }
    }
    return 0;
}
