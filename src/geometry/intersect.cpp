#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> point;
typedef pair<int, int> ii;
#define X first
#define Y second
#define F first
#define S second

int t;

void prt(int r) {
	if (r == 0) cout << "NO\n";
	else if (r == 1) cout << "POINT\n";
	else cout << "SEGMENT\n";
}

bool between(point p, point a, point b) {
	if (p.X == a.X && a.X == b.X) {
		if (a.Y > b.Y) swap(a, b);
		return a.Y <= p.Y && p.Y <= b.Y;
	}
	if (p.Y == a.Y && a.Y == b.Y) {
		if (a.X > b.X) swap(a, b);
		return a.X <= p.X && p.X <= b.X;
	}
}

int cross(point a, point b) {
	return a.X*b.Y-a.Y*b.X;
}

int main() {
	cin >> t;
	for (int ct = 0; ct < t; ++ct) {
		int x1, y1, x2, y2, x3, y3, x4, y4;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
		point a1 = {x1, y1};
		point a2 = {x2, y2};
		point b1 = {x3, y3};
		point b2 = {x4, y4};
		if (a1 == a2 && b1 == b2) {
			if (a1 == b1) prt(1);
			else prt(0);
			continue;
		}
		if (a1 == a2) {
			if (between(a1, b1, b2)) prt(1);
			else prt(0);
			continue;
		}
		if (b1 == b2) {
			if (between(b1, a1, a2)) prt(1);
			else prt(0);
			continue;
		}
		// now all lengths > 0
		// test for overlap
		if (a1.Y == a2.Y && a2.Y == b1.Y && b1.Y == b2.Y) {
			vector<ii> v;
			v.push_back({a1.X, 1});
			v.push_back({a2.X, 1});
			v.push_back({b1.X, 2});
			v.push_back({b2.X, 2});
			sort(v.begin(), v.end());
		}
	}
	return 0;
}
