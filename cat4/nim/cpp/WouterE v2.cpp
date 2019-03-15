#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;				// Brute force with cache
									// Runs in 50s with 400MB on release mode
									// Profiling: 50% of the time is spend on calculating hash
struct MyHash {						
	size_t operator () (const vector<int>& v) const {
		size_t result = 0;

		for (int x : v) {
			result += x;
			result *= 1009;
			result %= 100000000003;
		}

		return result;
	}
};

unordered_map<vector<int>, bool, MyHash> cache;

bool winning(const vector<int>& field) {
	if (cache.find(field) != cache.end()) return cache.at(field);

	for (int i = 0; i < field.size(); i++) {
		for (int y = 0; y < field.at(i); y++) {
			auto tmp = field;
			tmp.erase(tmp.begin() + i);
			if(y > 0) tmp.insert(upper_bound(tmp.begin(), tmp.end(), y), y);

			if (!winning(tmp)) return cache[field] = true;
		}
	}

	return cache[field] = false;
}

int main() {
	cache[vector<int>()] = true;

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

				auto key = next;
				sort(key.begin(), key.end());
				key.erase(key.begin(), upper_bound(key.begin(), key.end(), 0));
				
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
		
		if(!win) {
			cout << i << " HOPELOOS" << endl;
		}
	}
}
