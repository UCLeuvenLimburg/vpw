#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int inf = 1'000'000'000;

struct ii { int d, p; };
using vii = vector<ii>;
using vb = vector<bool>;

vii flights, airplanes;
map<pair<vb, vb>, int> cache;

int solve(vb fs, vb as) {
	if (cache.find({ fs, as }) != cache.end()) {
		return cache.at({ fs, as });
	}

	if (all_of(fs.begin(), fs.end(), [](bool b) { return b; })) {
		return 0;
	}

	int min = inf;

	for (int a = 0; a < flights.size(); a++) {
		if (!fs.at(a))
		{
			int best = inf;
			int b = -1;
			for (int i = 0; i < airplanes.size(); i++) {
				if (!as.at(i) && 
					airplanes.at(i).p >= flights.at(a).p && 
					airplanes.at(i).d >= flights.at(a).d)
				{
					int cost = (airplanes.at(i).p - flights.at(a).p) * flights.at(a).d;

					if (cost < best) {
						best = cost;
						b = i;
					}
				}
			}

			if (b != -1) {
				fs.at(a) = true;
				as.at(b) = true;

				int result = best + solve(fs, as);
				if (result < min) {
					min = result;
				}

				as.at(b) = false;
				fs.at(a) = false;
			}
		}
	}

	cache[{fs, as}] = min;
	return min;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int fs, as;
		cin >> fs >> as;

		cache.clear();
		flights.clear();
		airplanes.clear();
		for (int j = 0; j < fs; j++) {
			int d, p;
			cin >> d >> p;
			flights.push_back({ d, p });
		}
		for (int j = 0; j < as; j++) {
			int d, p;
			cin >> d >> p;
			airplanes.push_back({ d, p });
		}

		int result = solve(vb(flights.size(), false), vb(airplanes.size(), false));
		if (result == inf) {
			cout << i << " geen oplossing" << endl;
		}
		else {
			cout << i << " " << result << endl;
		}
	}
}
