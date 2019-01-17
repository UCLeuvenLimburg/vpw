#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i = int;
using vi = vector<i>;
struct ii { i n, r; };
using vii = vector<ii>;
struct C { i x, y, r; };
using vc = vector<C>;

int dist(C c1, C c2) {
	return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
}

double min_dist(const vc& cirkels, C cirkel) {
	double min = 1'000'000'000.0;

	for (C c : cirkels) {
		if (c.x != cirkel.x && c.y != cirkel.y) {
			double d = sqrt(dist(c, cirkel)) - c.r - cirkel.r;
			if (d < min) min = d;
		}
	}

	return min;
}

bool possible(vc cs, vii sets) {
	sort(sets.begin(), sets.end(), [](ii l, ii r) { return l.r > r.r; });

	for (ii nr : sets) {
		auto it = max_element(cs.begin(), cs.end(), [&cs](C c1, C c2) {return c1.r > 0 ? true : c2.r > 0 ? false : min_dist(cs, c1) < min_dist(cs, c2); });

		(*it).r = nr.r;
	}

	for (int i = 0; i < cs.size(); i++) {
		for (int j = i + 1; j < cs.size(); j++) {
			if (dist(cs.at(i), cs.at(j)) <= (cs.at(i).r + cs.at(j).r) * (cs.at(i).r + cs.at(j).r)) {
				return false;
			}
		}
	}

	return true;
}

int solve(const vc& cirkels, const vi& getallen, const vii& sets, int index) {
	if (index == getallen.size()) return 0;

	int max = 0;

	for (int i = 0; i < sets.size(); i++) {
		vii tmp(sets);
		ii& p = tmp.at(i);

		int prev = p.n * p.r;

		p.n++;
		p.r += getallen.at(index);

		int score = p.n * p.r - prev;
		if (possible(cirkels, tmp)) score += solve(cirkels, getallen, tmp, index + 1);
		if (score > max) max = score;
	}

	if(sets.size() < cirkels.size()){
		vii tmp(sets);
		tmp.push_back({1, getallen.at(index)});

		int score = getallen.at(index);
		if(possible(cirkels, tmp)) score += solve(cirkels, getallen, tmp, index + 1);
		if (score > max) max = score;
	}

	return max;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int cs, gs;
		cin >> cs >> gs;

		vc cirkels;
		for (int a = 0; a < cs; a++) {
			int x, y;
			cin >> x >> y;
			cirkels.push_back({ x, y, 0});
		}

		vi getallen;
		for (int a = 0; a < gs; a++) {
			int x;
			cin >> x;
			getallen.push_back(x);
		}

		cout << i << " " << solve(cirkels, getallen, vii(), 0) << endl;
	}
}