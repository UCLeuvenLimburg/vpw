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
map<vb, int> cache;

int solve(int flight, vb as) {
	if (flight == flights.size()) return 0;
	if (cache.find(as) != cache.end()) return cache.at(as);

	int min = inf;

	for (int a = 0; a < airplanes.size(); a++) {
		if (!as.at(a) && flights.at(flight).d <= airplanes.at(a).d && flights.at(flight).p <= airplanes.at(a).p)
		{
			as.at(a) = true;
			int cost = flights.at(flight).d * (airplanes.at(a).p - flights.at(flight).p);
			min = std::min(min, cost + solve(flight + 1, as));
			as.at(a) = false;
		}
	}

	return cache[as] = min;
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

		int result = solve(0, vb(airplanes.size(), false));
		if (result == inf) {
			cout << i << " geen oplossing" << endl;
		}
		else {
			cout << i << " " << result << endl;
		}
	}
}
