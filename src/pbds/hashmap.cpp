#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

// get a random number
uint32_t rd() {
	uint32_t ret;
	asm volatile("rdrand %0" :"=a"(ret) ::"cc");
	return ret;
}

const uint32_t XR = rd();

// xor with a random number to avoid anti-hash tests
struct chash {
    int operator()(int x) const { return hash<int>{}(x^XR); }
};

int n;
gp_hash_table<ll, int, chash> s;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		s[x] = 1;
	}
	cout << s.size() << "\n";
	return 0;
}
