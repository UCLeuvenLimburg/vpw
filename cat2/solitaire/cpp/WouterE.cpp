#include <iostream>
#include <algorithm>

using namespace std;

const int max_length = 20;
int32_t cache[1 << max_length];

int index_of_lowest_set_bit(int32_t field) {
	if (field == 0x7FFF'FFFF) return 0;
	int index = 0;
	while (!(field & (1 << index))) index++;
	return index + 1;
}

int32_t lowest_set_unique_bit(int32_t field) {
	if (field & (field - 1)) return 0x7FFF'FFFF;
	return (field & -field);
}

int32_t solve(int32_t field) {
	if (cache[field] != 0) return cache[field];
	if (!(field & (field >> 1))) return cache[field] = lowest_set_unique_bit(field);

	int32_t min = 0x7FFF'FFFF;
	for (uint32_t jumps : { 
		(field >> 1) & field & ~(field << 1), 
		(field << 1) & field & ~(field >> 1) 
	}) {
		for (int i = 1; i < max_length - 1; i++) {
			if (jumps & (1 << i)) {
				min = std::min(min, solve(field ^ (1 << (i - 1)) ^ (1 << (i + 0)) ^ (1 << (i + 1))));
			}
		}
	}
	return cache[field] = min;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int l;
		cin >> l;

		int32_t field = 0;
		for (int j = 0; j < l; j++) {
			int32_t x;
			cin >> x;
			field |= x << j;
		}

		int sol = index_of_lowest_set_bit(solve(field));
		if (sol == 0 || sol > l) cout << i << " ONMOGELIJK" << endl;
		else cout << i << " " << sol << endl;
	}
}
