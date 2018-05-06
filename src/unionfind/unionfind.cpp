#include <iostream>
#include <algorithm>

using namespace std;

int k[100005];
int s[100005];

int id(int x) {
	int tx = x;
	while (k[x] != x) x = k[x];
	return k[tx] = x;
}

bool equal(int a, int b) {
	return id(a) == id(b);
}

void join(int a, int b) {
	a = id(a);
	b = id(b);
	if (s[b] > s[a]) swap(a, b);
	s[a] += s[b];
	k[b] = a;
}

int n;

int main() {
	for (int i = 0; i < n; ++i) {
		k[i] = i;
		s[i] = 1;
	}
}
