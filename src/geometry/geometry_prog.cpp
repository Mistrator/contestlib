#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long double ct; // coordinate type
typedef complex<ct> point;
#define X real()
#define Y imag()
#define F first
#define S second

const ct EPS = 0.000000001; // 1e-9
const ct PI = 3.14159265359;

// floating-point equality comparison
bool equal(ct a, ct b) {
	return abs(a-b) < EPS;
}

// point equality comparison
bool equal(point a, point b) {
	return (equal(a.X, b.X) && equal(a.Y, b.Y));
}

// comparer for sorting points
// check if a < b
bool point_comp(point a, point b) {
	if (equal(a.X, b.X)) {
		return a.Y < b.Y;
	}
	return a.X < b.X;
}

struct line {
	point first, second;

	line(point a, point b) {
		if (point_comp(b, a)) swap(a, b);
		first = a;
		second = b;
	}

	// construct line from point and angle of elevation
	line(point a, ct ang) : line(a, a+polar((ct)1.0, ang)) {}

	// construct line from standard equation coefficients
	// assume that a != 0 or b != 0
	// TESTED
	line(ct a, ct b, ct c) {
		if (equal(b, 0.0)) {
			// vertical line
			ct cx = c/(-a);
			first = {cx, 0};
			second = {cx, 1};
		}
		else {
			first = {0, c/(-b)};
			second = {1, (a+c)/(-b)};
		}
		if (point_comp(second, first)) swap(first, second);
	}
};

struct line_segment {
	point first, second;

	// implicit conversion
	operator line() {
		return line(first, second);
	}

	line_segment(point a, point b) {
		if (point_comp(b, a)) swap(a, b);
		first = a;
		second = b;
	}

	line_segment(point a, ct ang, ct len) : line_segment(a, a+polar(len, ang)) {};
};

// assume that the first and last vertices are the same
typedef vector<point> polygon;

// radians to degrees
ct rad_to_deg(ct arad) {
	return (arad*((ct)180.0/PI));
}

// degrees to radians
ct deg_to_rad(ct adeg) {
	return (adeg*(PI/(ct)180.0));
}

// dot product, > 0 if a, b point to same direction, 0 if perpendicular, < 0 if pointing to opposite directions
ct dot(point a, point b) {
	return (conj(a)*b).X;
}

// 2D cross product, > 0 if a+b turns left, 0 if collinear, < 0 if turns right
ct cross(point a, point b) {
	return (conj(a)*b).Y;
}

// euclidean distance
// TESTED
ct dist(point a, point b) {
	return abs(a-b);
}

// squared distance
ct sq_dist(point a, point b) {
	return norm(a-b);
}

// angle from a to b
// [0, 2*pi[
// TESTED
ct angle(point a, point b) {
	ct cres = arg(b-a);
	if (cres < 0) cres = 2*PI+cres;
	return cres;
}

// angle of elevation
// [-pi/2, pi/2]
ct elev_ang(point a, point b) {
	if (point_comp(b, a)) swap(a, b);
	return arg(b-a);
}

// angle of elevation
ct elev_ang(line l) {
	return elev_ang(l.F, l.S);
}

// slope of line
ct slope(point a, point b) {
	return tan(elev_ang(a, b));
}

// slope of line
ct slope(line l) {
	return tan(elev_ang(l));
}

// length of line segment
ct segment_len(line_segment ls) {
	return dist(ls.F, ls.S);
}

// rotate a around origin by ang
point rot_origin(point a, ct ang) {
	return (a*polar((ct)1.0, ang));
}

// rotate a around ps by ang
point rot_pivot(point a, point ps, ct ang) {
	return ((a-ps)*polar((ct)1.0, ang)+ps);
}

// translate a by dist to the direction of ang
point translate(point a, ct dist, ct ang) {
	return a+polar(dist, ang);
}

// check if a -> b -> c turns counterclockwise
bool ccw(point a, point b, point c) {
	return cross({b.X-a.X, b.Y-a.Y}, {c.X-a.X, c.Y-a.Y}) > 0;
}

// < 0 if point is left, ~0 if on line, > 0 if right
// TESTED
ct point_line_side(point a, line l) {
	return cross(a-l.F, a-l.S);
}

// check if point is on line
// TESTED
bool point_on_line(point a, line l) {
	return equal(point_line_side(a, l), (ct)0.0);
}

// check if point is on line segment
// TESTED
bool point_on_seg(point a, line_segment ls) {
	if (!point_on_line(a, ls)) return false;
	if (equal(a, ls.F) || equal(a, ls.S)) return true;
	return (point_comp(ls.F, a) && point_comp(a, ls.S));
}

// get projection of a on l
// TESTED
point point_line_proj(point a, line l) {
	return (l.F+(l.S-l.F)*dot(a-l.F, l.S-l.F)/norm(l.S-l.F));
}

// reflect a across l
point point_line_refl(point a, line l) {
	return (l.F+conj((a-l.F)/(l.S-l.F))*(l.S-l.F));
}

// angle a-b-c
// [0, PI]
// TESTED
ct ang_abc(point a, point b, point c) {
	return abs(remainder(arg(a-b)-arg(c-b), (ct)2.0*PI));
}

// shortest distance between point a and line l
// TESTED
ct point_line_dist(point a, line l) {
	point proj = point_line_proj(a, l);
	return dist(a, proj);
}

// shortest distance between point a and line segment ls
// TESTED
ct point_segment_dist(point a, line_segment ls) {
	point proj = point_line_proj(a, ls);
	if (point_on_seg(proj, ls)) {
		return dist(a, proj);
	}
	return min(dist(a, ls.F), dist(a, ls.S));
}

// get intersection point of two lines
// first return val 0 = no intersection, 1 = single point, 2 = infinitely many
// second return val = intersection point if first return val = 1, otherwise undefined
// TESTED (only non-degenerate cases, single intersection point)
pair<int, point> intersect(line a, line b) {
	ct c1 = cross(b.F-a.F, a.S-a.F);
	ct c2 = cross(b.S-a.F, a.S-a.F);
	if (equal(c1, c2)) {
		if (point_on_line(b.F, a)) {
			return {2, a.F};
		}
		return {0, a.F};
	}
	return {1, (c1*b.S-c2*b.F)/(c1-c2)};
}

// sort comparer for seg_intersect
bool pi_comp(pair<point, int> p1, pair<point, int> p2) {
	if (equal(p1.F, p2.F)) return p1.S < p2.S;
	return point_comp(p1.F, p2.F);
}

// get intersection point of two line segments
// first return val 0 = no intersection, 1 = single point, 2 = infinitely many
// second return val = intersection point if first return val = 1, otherwise undefined
pair<int, point> seg_intersect(line_segment a, line_segment b) {
	ct alen = segment_len(a);
	ct blen = segment_len(b);

	if (equal(alen, (ct)0) && equal(blen, (ct)0)) {
		return (equal(a.F, b.F) ? make_pair(1, a.F) : make_pair(0, a.F));
	}
	else if (equal(alen, (ct)0)) {
		return (point_on_seg(a.F, b) ? make_pair(1, a.F) : make_pair(0, a.F));
	}
	else if (equal(blen, (ct)0)) {
		return (point_on_seg(b.F, a) ? make_pair(1, b.F) : make_pair(0, b.F));
	}

	auto tres = intersect(a, b);
	if (tres.F == 0) {
		return tres;
	}
	else if (tres.F == 2) {
		vector<pair<point, int>> v = {{a.F, 1}, {a.S, 1}, {b.F, 2}, {b.S, 2}};
		sort(v.begin(), v.end(), pi_comp);
		if (v[0].S != v[1].S) return {2, a.F}; // overlapping segments

		// common vertex
		if (equal(a.S, b.F)) return {1, a.S};
		if (equal(a.F, b.S)) return {1, a.F};

		// not intersecting but on the same line
		return {0, a.F};
	}
	if (point_on_seg(tres.S, a) && point_on_seg(tres.S, b)) {
		return tres;
	}
	return {0, a.F};
}

// get polygon area
// O(n)
// TESTED
ct pgon_area(polygon pg) {
	ct cres = 0;
	for (int i = 0; i < pg.size()-1; ++i) {
		cres += cross(pg[i], pg[i+1]);
	}
	return (abs(cres)/(ct)2.0);
}

// check if point is inside polygon
// 0 = outside, 1 = inside, 2 = on polygon edge
// O(n)
// INCORRECT
int point_in_pgon(point a, polygon pg) {
	for (int i = 0; i < pg.size()-1; ++i) {
		if (point_on_seg(a, line_segment(pg[i], pg[i+1]))) {
			return 2;
		}
	}
	// arbitrary angle, try to avoid polygon vertices (likely lattice points)
	line_segment tl = line_segment(a, {(ct)1045366375, (ct)2894362571});
	int icnt = 0;
	for (int i = 0; i < pg.size()-1; ++i) {
		auto cur = seg_intersect(tl, line_segment(pg[i], pg[i+1]));
		if (cur.F > 0) {
			icnt++;
		}
	}
	return (icnt%2 == 1);
}

// return the points that form given point set's convex hull
// O(n log n)
vector<point> convex_hull(vector<point> ps) {
	vector<point> ch;
	sort(ps.begin(), ps.end(), point_comp);
    for (int cv = 0; cv < 2; ++cv) {
        for (int i = 0; i < ps.size(); ++i) {
            int cs = ch.size();
            while (cs >= 2 && ccw(ch[cs-2], ch[cs-1], ps[i])) {
                ch.pop_back();
                --cs;
            }
            ch.push_back(ps[i]);
        }
        ch.pop_back();
        reverse(ps.begin(), ps.end());
    }
    return ch;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return 0;
}
