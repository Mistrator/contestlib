#include <iostream>

using namespace std;
typedef long long ll;

const int N = 1<<11;

int n, q;

ll st[2*N][2*N];

// calculate subgrid sum from {y1, x1} to {y2, x2}
// 0-indexed
ll summa(int y1, int x1, int y2, int x2) {
    y1 += N;
    x1 += N;
    y2 += N;
    x2 += N;
    
    ll sum = 0;
    
    while (y1 <= y2) {
        if (y1%2 == 1) {
            int nx1 = x1;
            int nx2 = x2;
            while (nx1 <= nx2) {
                if (nx1%2 == 1) sum += st[y1][nx1++];
                if (nx2%2 == 0) sum += st[y1][nx2--];
                nx1 /= 2;
                nx2 /= 2;
            }
            y1++;
        }
        if (y2%2 == 0) {
            int nx1 = x1;
            int nx2 = x2;
            while (nx1 <= nx2) {
                if (nx1%2 == 1) sum += st[y2][nx1++];
                if (nx2%2 == 0) sum += st[y2][nx2--];
                nx1 /= 2;
                nx2 /= 2;
            }
            y2--;
        }
        y1 /= 2;
        y2 /= 2;
    }
    return sum;
}

// set {y, x} to u
// 0-indexed
void muuta(int y, int x, ll u) {
    y += N;
    x += N;
    st[y][x] = u;
    for (int nx = x/2; nx >= 1; nx /= 2) {
        st[y][nx] = st[y][2*nx]+st[y][2*nx+1];
    }
    
    for (y /= 2; y >= 1; y /= 2) {
        for (int nx = x; nx >= 1; nx /= 2) {
            st[y][nx] = st[2*y][nx]+st[2*y+1][nx];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll a;
            cin >> a;
            muuta(i, j, a);
        }
    }
    
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int y, x, u;
            cin >> y >> x >> u;
            muuta(y-1, x-1, u);
        }
        if (tp == 2) {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << summa(y1-1, x1-1, y2-1, x2-1) << "\n";
        }
    }   
    return 0;
} 
