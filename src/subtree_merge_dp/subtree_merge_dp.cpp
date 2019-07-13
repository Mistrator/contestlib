#include <iostream>
#include <vector>

using namespace std;

const int N = 3005;
const int INF = 1000000005;

int n, m;
vector<int> g[N];

int sz[N];
// dp[i][j] = min number of blocked edges to get a security zone of
// size j in the subtree of vertex i such that i is in the zone
int dp[N][N];

// Looking for a challenge: Barricades style
// Merge child subtrees of s to s one-by-one
// Runs in O(n^2) even though it looks like O(n^3)
void solve(int s, int p) {
	// maintain the combined size of already merged child subtrees
	sz[s] = 1;

	// initial dp conditions (how to solve if s is a leaf node)
	dp[s][1] = 0;

	// merge the subtree of v to (s + previous v:s)
	// first v requires no special case, since we just merge to s
	for (int v : g[s]) {
		if (v == p) continue;
		solve(v, s);

		// take a elements from already merged ones and b from the subtree of v
		// we don't need an auxiliary dp array since we write to larger indices than
		// from where we read during current subtree merge operation ((a+b) > a)
		for (int a = sz[s]; a >= 0; --a) {
			for (int b = 0; b <= sz[v]; ++b) {
				// do dp transition here
				dp[s][a+b] = min(dp[s][a+b], dp[s][a] + dp[v][b]);
			}

			// Barricades specific: if we take 0 nodes from v, we have to
			// block the edge to v
			// In Barricades, innermost loop should start from b=1
			// dp[s][a]++;
		}
		// now v is completely merged, count its size
		sz[s] += sz[v];
	}
}

int main() {
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			dp[i][j] = INF;
		}
	}
	solve(1, -1);
	return 0;
}
