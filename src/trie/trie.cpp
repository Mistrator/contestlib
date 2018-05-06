#include <iostream>
#include <string>

using namespace std;

const int LC = 26; // letter count

struct node {
	bool endp;
	node* ch[LC];

	node() {
		for (int i = 0; i < LC; ++i) {
			ch[i] = nullptr;
		}
	}
};

void insert(node* root, string cs) {
	
}