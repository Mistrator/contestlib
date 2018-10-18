#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string s;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	vector<pair<string, int>> v;
	for (int i = s.length()-1; i >= 0; --i) {
		v.push_back({s.substr(i, string::npos), i});
	}
	sort(v.begin(), v.end());
	for (auto a : v) {
		cout << a.second << " ";
	}
	cout << endl;
	return 0;
}
