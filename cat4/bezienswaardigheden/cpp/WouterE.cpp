#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const double inf = numeric_limits<double>::infinity();
using vd = vector<double>;
struct ii { int x, y; };
using vii = vector<ii>;

vii punten;

double dist(int i, int j) {
	ii& l = punten.at(i);
	ii& r = punten.at(j);
	return sqrt((l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y));
}

double dist_range(int i, int j) {
	double result = 0.0;
	for (int k = i; k < j; k++) {
		result += dist(k, k + 1);
	}
	return result;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ps;
		cin >> ps;

		punten.clear();

		for (int j = 0; j < ps; j++) {
			int x, y;
			cin >> x >> y;
			punten.push_back({ x, y });
		}

		sort(punten.begin(), punten.end(), [](ii l, ii r) { return l.x < r.x; });

		vd best(1, 0.0);

		for (int i = 1; i < punten.size() - 1; i++) {
			double min = inf;

			for (int j = 0; j < i; j++) {
				double distance = best.at(j) + dist(j, i + 1) + dist_range(j + 1, i);
				if (distance < min) min = distance;
			}

			best.push_back(min);
		}

		cout << i << " " << (unsigned)(dist(0, 1) + best.back() + dist(ps - 2, ps - 1) + 0.5) << endl;
	}
}
