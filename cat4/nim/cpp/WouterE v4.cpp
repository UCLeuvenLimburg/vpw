#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;								// Brute force that uniquely encodes state as 64-bit to speed up
													// Abuses knowledge of input: handles big numbers in the state differently
using ll = long long;								// Runs in around 14s

unordered_map<ll, bool> cache, big_cache;

bool winning(ll field) {
	if (cache.find(field) != cache.end()) return cache.at(field);

	for (int heap_size = 1; heap_size < 15; heap_size++) {
		int index = (heap_size - 1) * 4;
		ll freq = (field >> index) & 15;
		if (freq > 0) 
		{
			for (int y = 0; y < heap_size; y++) {
				ll next = field;

				next &= ~(15LL << index);
				next |= (freq - 1) << index;

				if (y > 0) {
					int new_index = (y - 1) * 4;
					ll new_freq = (field >> new_index) & 15;

					next &= ~(15LL << new_index);
					next |= (new_freq + 1) << new_index;
				}
				
				if (!winning(next)) return cache[field] = true;
			}
		}
	}

	return cache[field] = false;
}

bool big_winning(ll field) {
	if (big_cache.find(field) != big_cache.end()) return big_cache.at(field);

	int index = 0;
	ll sub = field;
	while (sub > 0) {
		for (ll freq = 0; freq < (sub & 511); freq++) {
			ll next = field;
			
			next &= ~(511LL << index);
			next |= freq << index;

			if (!big_winning(next)) return big_cache[field] = true;
		}

		index += 9;
		sub >>= 9;
	}

	return big_cache[field] = false;
}

int main() {
	cache[0] = true;
	big_cache[0] = true;

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

				if (max < 16) {
					ll key = 0;
					for (int a = max; a >= 1; a--) {
						key = key * 16 + count(next.begin(), next.end(), a);
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
				else {
					ll key = 0;
					for (int x : next) {
						key = key * 512 + x;
					}

					if (!big_winning(key)) {
						win = true;

						cout << i;
						for (int z : next) {
							cout << " " << z;
						}
						cout << endl;
					}
				}
			}
		}

		if (!win) {
			cout << i << " HOPELOOS" << endl;
		}
	}
}
