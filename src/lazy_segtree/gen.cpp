#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int n, q, mx;

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	srand(time(NULL));
	n = stoi(argv[1]);
	q = stoi(argv[2]);
	mx = stoi(argv[3]);
	cout << n << " " << q << "\n";
	for (int i = 0; i < n; ++i) {
		cout << rand()%mx + 1 << " ";
	}
	cout << "\n";
	for (int i = 0; i < q; ++i) {
		int clo = rand()%n+1;
		int chi = rand()%n+1;
		if (clo > chi) swap(clo, chi);
		if (rand()%2 == 0) {
			cout << "1 " << clo << " " << chi << " " << rand()%mx+1 << "\n";
		}
		else {
			cout << "2 " << clo << " " << chi << "\n";
		}
	}
	return 0;
}
