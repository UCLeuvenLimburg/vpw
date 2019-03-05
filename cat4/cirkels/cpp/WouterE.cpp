#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct ii { int n, r; };
struct C { int x, y, r; };

vector<C> cirkels;
vector<int> getallen;

int dist(C c1, C c2) {
	return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
}

double min_dist(const vector<C>& cs, C cirkel) {
	double min = 1'000'000'000.0;

	for (C c : cs) {
		if (c.x != cirkel.x && c.y != cirkel.y) {
			min = std::min(min, sqrt(dist(c, cirkel)) - c.r - cirkel.r);
		}
	}

	return min;
}

bool end_of_game(vector<ii> bins) {
	sort(bins.begin(), bins.end(), [](ii l, ii r) { return l.r > r.r; });
	vector<C> cs = cirkels;

	for (ii bin : bins) {
		auto it = max_element(cs.begin(), cs.end(), [cs](C c1, C c2) { 
			if ((c1.r > 0) != (c2.r > 0)) return c1.r > 0;
			return min_dist(cs, c1) < min_dist(cs, c2); 
		});

		(*it).r = bin.r;

		if (min_dist(cs, *it) <= 0) return true;
	}

	return false;
}

int solve(const vector<ii>& bins, int index) {
	if (index == getallen.size() || end_of_game(bins)) {
		int sum = 0;
		for (ii p : bins) sum += p.n * p.r;
		return sum;
	}

	int max = 0;

	for (int i = 0; i < bins.size(); i++) {
		vector<ii> tmp = bins;
		if (tmp.at(i).n == 0 && tmp.size() < cirkels.size()) tmp.push_back({ 0, 0 });

		tmp.at(i).n++;
		tmp.at(i).r += getallen.at(index);

		max = std::max(max, solve(tmp, index + 1));
	}

	return max;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int cs, gs;
		cin >> cs >> gs;

		cirkels = vector<C>(cs, { 0, 0, 0 });
		for (int a = 0; a < cs; a++) cin >> cirkels.at(a).x >> cirkels.at(a).y;

		getallen = vector<int>(gs);
		for (int a = 0; a < gs; a++) cin >> getallen.at(a);

		cout << i << " " << solve({ {0, 0} }, 0) << endl;
	}
}
