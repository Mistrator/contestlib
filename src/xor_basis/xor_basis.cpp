int basis[d]; // basis[i] is the vector whose f value is i
int sz; // current size of the basis

// check if a vector can be represented with current basis
// if not, add it to the basis
void insert_vector(int mask) {
	for (int i = 0; i < d; i++) {
		if ((mask&(1<<i)) == 0) continue;
		if (basis[i] == 0) { 
			// if there is no basis vector with the i'th bit set, then insert this vector into the basis
			basis[i] = mask;
			sz++;
			return;
		}
		// otherwise subtract the basis vector from this vector
		mask ^= basis[i];
	}
}

// check whether a vector can be represented as a linear
// combination of current basis vectors
bool can_represent(int mask) {
	for (int i = 0; i < 20; ++i) {
		if ((mask&(1<<i)) == 0) continue;
		if (basis[i] == 0) {
			return false;
		}
		mask ^= basis[i];
	}
	return mask == 0;
}
