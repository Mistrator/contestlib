// creates a circular suffix array (sorted array of cyclic rotations)
// to get a normal suffix array, add $ to the end of the string
// and discard the first element of returned suffix array
// n = 7*10^5 takes around 1 second
vector<int> suffix_array(string cs) {
	int cn = (int)cs.length();
	int MXN = cn+256; // size of alphabet
	vector<int> sa(cn), ra(cn);

	for (int i = 0; i < cn; ++i) {
		sa[i] = i;
		ra[i] = (int)cs[i];
	}

	for (int k = 0; k < cn; k ? k *= 2 : ++k) {
		vector<int> nsa(sa), nra(cn), ccnt(MXN);
		for (int i = 0; i < cn; ++i) {
			nsa[i] = (nsa[i]-k+cn)%cn;
			ccnt[ra[i]]++;
		}
		for (int i = 1; i < MXN; ++i) {
			ccnt[i] += ccnt[i-1];
		}
		for (int i = cn-1; i >= 0; --i) {
			sa[--ccnt[ra[nsa[i]]]] = nsa[i];
		}
		int r = 0;
		for (int i = 1; i < cn; ++i) {
			if (ra[sa[i]] != ra[sa[i-1]]) {
				r++;
			}
			else if (ra[(sa[i] + k)%cn] != ra[(sa[i-1] + k)%cn]) {
				r++;
			}
			nra[sa[i]] = r;
		}
		ra = nra;
	}
	return sa;
}
