#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef __int128 lll;

ll n;

ll f(lll x) {
    return (x*x+1)%n;
}

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

// return a factor of a
// st is a starting seed for pseudorandom numbers, start with 2, if algorithm fails (returns -1), increment seed
ll pollardrho(ll a, ll st) {
    if (n%2 == 0) return 2;
    
    ll x = st, y = st, d = 1;
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(abs(x-y), a);
        if (d == a) return -1;
    }
    return d;
}

/*
	TESTED, correct.
    Finds a factor of n in O(root_4(n))
    If n is prime, alg might not terminate or it might return 1. Check for primality.

    TODO: check for perfect square
*/
int main() {
    cin >> n;
    ll fa = -1;
    ll st = 2;
    while (fa == -1) {
        fa = pollardrho(n, st++);
    }
    cout << min(fa, n/fa) << " " << max(fa, n/fa) << "\n";
    return 0;
}
