#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int inf = 1'000'000'000;

string zin, correct;
vector<vector<int>> edit_distance;

int solve(int p1, int p2) {
	if (p1 < 0 || p2 < 0) return max((p1 + 1) * 2, 0) + max((p2 + 1) * 2, 0);
	if (edit_distance.at(p1).at(p2) < inf) return edit_distance.at(p1).at(p2);
	return edit_distance.at(p1).at(p2) = min(min(
		solve(p1 - 1, p2) + 2,
		solve(p1, p2 - 1) + 2),
		solve(p1 - 1, p2 - 1) + (
			zin.at(p1) == correct.at(p2) ? 0 :
			tolower(zin.at(p1)) == tolower(correct.at(p2)) ? 1 : 2
		)
	);
}

int main() {
	int n;
	cin >> n;
	getline(cin, zin);

	for (int i = 1; i <= n; i++) {
		getline(cin, zin);
		getline(cin, correct);
		edit_distance = vector<vector<int>>(zin.size(), vector<int>(correct.size(), inf));
		cout << i << " " << solve(zin.size() - 1, correct.size() - 1) << endl;
	}
}
