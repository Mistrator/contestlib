#include <iostream>
#include <random>

using namespace std;

int main() {
	random_device rd; // seeds the PRNG, gets random data from OS
	mt19937 mt(rd());

	uniform_int_distribution<int> int_dist(1, 10); // inclusive [1, 10]
	uniform_real_distribution<double> double_dist(1.0, 10.0); // exclusive [1.0, 10.0[

	for (int i = 0; i < 10; ++i) {
		cout << int_dist(mt) << " " << double_dist(mt) << "\n";
	}
}
