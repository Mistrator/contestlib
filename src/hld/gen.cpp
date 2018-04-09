#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int n, m, x;

void prtq() {
	int a, b;
	do {
		a = rand()%n+1;
		b = rand()%n+1;
	} while (a == b);
	cout << "1 " << a << " " << b << "\n";
}

void prtc() {
	int a, b;
	do {
		a = rand()%n+1;
		b = rand()%n+1;
	} while (a == b);
	cout << "2 " << a << " " << b << " " << rand()%x+1 << "\n";
}

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	srand(time(NULL));
	n = stoi(argv[1]);
	m = stoi(argv[2]);
	x = stoi(argv[3]);

	cout << n << " " << m << "\n";
	for (int i = 2; i <= n; ++i) {
		cout << i << " " << (rand()%(i-1))+1 << "\n";
	}
	for (int i = 0; i < m-1; ++i) {
		int tp = rand()%2;
		if (tp == 0) {
			prtq();
		}
		else {
			prtc();
		}
	}
	prtq(); 
	return 0;
}
