#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef long long ll;

int n;
ll mx;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	n = stoi(argv[1]);
	mx = stol(argv[2]);

	cout << n << "\n";

	for (int i = 0; i < n; ++i) {
		cout << rand()%mx+1 << " ";
	}
	cout << "\n";
	return 0;
}
