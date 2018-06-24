#include <deque>

template <typename T>
struct kmax_queue {
private:
	std::deque<std::pair<T, int>> q;
	int q_size;

public:
	kmax_queue() {
		q_size = 0;
	}

	void push_back(T x) {
		int unimp_before = 0;

		while ((!q.empty()) && (q.back().first <= x)) {
			unimp_before += q.back().second + 1;
			q.pop_back();
		}

		q.push_back({x, unimp_before});
		q_size++;
	}

	void pop_front() {
		if (empty()) {
			throw ("The queue is empty");
		}

		if (q.front().second > 0) {
			q.front().second--;
		}
		else {
			q.pop_front();
		}

		q_size--;
	}

	T max() {
		if (empty()) {
			throw ("The queue is empty");
		}

		return q.front().first;
	}

	int size() {
		return q_size;
	}

	bool empty() {
		return size() == 0;
	}
};
