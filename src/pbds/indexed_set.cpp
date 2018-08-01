#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

indexed_set s;

int main() {
	s.insert(2);
	s.insert(4);
	s.insert(5);

	auto x = s.find_by_order(1);
	cout << *x << "\n"; // prints 4

	cout << s.order_of_key(5) << "\n"; // prints 2
	cout << s.order_of_key(3) << "\n"; // prints 1
	return 0;
}
