#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
using ii = pair<int, int>;

vector<string> kaart;

ii move(ii p, char c) {
	if (c == 'L' && p.first > 0) p.first--;
	if (c == 'B' && p.second > 0) p.second--;
	if (c == 'O' && p.second < kaart.size() - 1) p.second++;
	if (c == 'R' && p.first < kaart.at(0).size() - 1) p.first++;
	return p;
}

ii walk(ii p, string pad) {
	if (pad.front() != kaart.at(p.second).at(p.first)) return { -1, -1 };
	if (pad.size() == 1) return { p.first + 1, p.second + 1 };
	return walk(move(p, pad.at(1)), pad.substr(2));
}

set<ii> solve(string pad) {
	set<ii> result;
	for (int i = 0; i < kaart.at(0).size(); i++) {
		for (int j = 0; j < kaart.size(); j++) {
			result.insert(walk({ i, j }, pad));
		}
	}
	return result;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int r, k;
		cin >> r >> k;

		kaart = vector<string>(r, "");
		for (int j = 0; j < r; j++) cin >> kaart.at(j);

		int l;
		string pad;
		cin >> l >> pad;

		auto sol = solve(pad);
		sol.erase({ -1, -1 });

		cout << i;
		for (auto p : sol) cout << " (" << p.first << "," << p.second << ")";
		if (sol.empty()) cout << " ONMOGELIJK";
		cout << endl;
	}
}
