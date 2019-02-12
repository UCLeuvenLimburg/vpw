#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int inf = 1'000'000'000;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int p;
		cin >> p;

		bool perfect_match = false;
		int sum = 0;
		set<int> data;
		for (int j = 0; j < p; j++) {
			int x, y;
			cin >> x >> y;
			sum = x + y;
			perfect_match |= !data.insert(x).second;
		}

		if (perfect_match) {
			cout << sum << endl;
		}
		else {
			int min_dif = inf;
			auto it = data.begin();
			auto it2 = ++data.begin();

			while (it2 != data.end()) {
				min_dif = min(min_dif, abs(*it2 - *it));
				it2++, it++;
			}

			cout << (sum + min_dif) << endl;
		}
	}
}
