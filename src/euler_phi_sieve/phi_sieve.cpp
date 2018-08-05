const int N = 100000;

int phi[N+5];

for (int i = 1; i <= N; ++i) {
	phi[i] += i;
	for (int j = 2*i; j <= N; j += i) {
		phi[j] -= phi[i];
	}
}
