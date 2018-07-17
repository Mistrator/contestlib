int n, q;

vector<int> g[N];
vector<int> nd[N]; // subtree root -> depth -> data, highest vertex is the last one

vector<int> nq[N]; // queries for each vertex
vector<pair<int, int>> rq; // raw queries in original order

map<int, int> res[N];

void dfs(int s, int p) {
	// find deepest subtree
	int mxs = 0, mxi = -1;
	for (int i = 0; i < g[s].size(); ++i) {
		int a = g[s][i];
		if (a == p) continue;
		dfs(a, s);
		if (nd[a].size() > mxs) {
			mxs = nd[a].size();
			mxi = i;
		}
	}
	// swap deepest subtree with current one
	if (mxi != -1) {
		swap(nd[s], nd[g[s][mxi]]);
	}
	// merge shallower subtrees to the largest one
	for (int i = 0; i < g[s].size(); ++i) {
		int a = g[s][i];
		if (a == p || i == mxi) continue;
		for (int j = 0; j < nd[a].size(); ++j) {
			int sr = nd[a].size()-(j+1); // source
			int de = nd[s].size()-(j+1); // destination
			// merge vertices with same depth
			nd[s][de] += nd[a][sr];
		}
	}
	// add current vertex
	nd[s].push_back(1);
	// nd[s] represents now the subtree of s
	// answer all queries on this subtree offline and store the answers
	for (int de : nq[s]) {
		int di = nd[s].size()-(de+1);
		if (di < 0) res[s][de] = 0;
		else res[s][de] = nd[s][di]-1;
	}
}

int main() {
	for (int i = 0; i < q; ++i) {
		// query vertex, query depth
		int cv, cd;
		cin >> cv >> cd;
		rq.push_back({cv, cd});
		nq[cv].push_back(cd);
	}
	dfs(1, -1); // start from the root
	// print query results in correct order
	for (int i = 0; i < q; ++i) {
		int cv = rq[i].first;
		int cd = rq[i].second;
		cout << res[cv][cd] << " ";
	}
	cout << "\n";
	return 0;
}
