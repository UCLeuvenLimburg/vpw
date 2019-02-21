#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;					// Brute force with updatable hash stored in vector itself
										// Runs very slowly at the end 
										// Profiling: Most of the time at the end is spent on comparing (= hash collisions because weak hash)
struct MyHash {
	size_t operator () (const vector<int>& v) const {
		return v.front();
	}
};

struct MyEqual {
	bool operator () (const vector<int>& l, const vector<int>& r) const {
		for (int i = 0; i < l.size() && i < r.size(); i++) {
			if (l.at(i) != r.at(i)) return false;
		}

		if (l.size() < r.size()) return count(r.begin() + l.size(), r.end(), 0) == r.size() - l.size();
		else return count(l.begin() + r.size(), l.end(), 0) == l.size() - r.size();
	}
};

unordered_map<vector<int>, bool, MyHash, MyEqual> cache;

int generate_value(int a, int b) {
	if (b == 0) return 0;
	return (a * 1'000'003) ^ (b * 100'000'007) ^ (a * b * 1'000'037);
}

bool winning(const vector<int>& field) {
	if (cache.find(field) != cache.end()) return cache.at(field);

	for (int i = 1; i < field.size(); i++) {
		if (field.at(i) > 0) {

			for (int y = 0; y < i; y++) {
				vector<int> next = field;

				next.at(i)--;
				next.at(0) ^= generate_value(i, next.at(i) + 1);
				next.at(0) ^= generate_value(i, next.at(i));

				if (y > 0) {
					next.at(y)++;
					next.at(0) ^= generate_value(y, next.at(y) - 1);
					next.at(0) ^= generate_value(y, next.at(y));
				}

				if (!winning(next)) return cache[field] = true;
			}

		}
	}

	return cache[field] = false;
}

int main() {
	cache[{ 0 }] = true;

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;

		vector<int> field(k);
		for (int j = 0; j < k; j++) cin >> field.at(j);

		bool win = false;
		for (int j = 0; j < k; j++) {
			for (int y = 0; y < field.at(j); y++) {
				vector<int> next = field;
				next.at(j) = y;

				int max = *max_element(next.begin(), next.end());

				vector<int> key(1, 0);
				for (int a = 0; a < max; a++) {
					key.push_back(count(next.begin(), next.end(), a + 1));
					key.at(0) ^= generate_value(a + 1, key.at(a + 1));
				}

				if (!winning(key)) {
					win = true;

					cout << i;
					for (int z : next) {
						cout << " " << z;
					}
					cout << endl;
				}
			}
		}

		if (!win) {
			cout << i << " HOPELOOS" << endl;
		}
	}
}
