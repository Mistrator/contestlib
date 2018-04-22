#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
	ll seed;
	asm("rdtsc" : "=A"(seed));
	srand(seed);
	return 0;
}
