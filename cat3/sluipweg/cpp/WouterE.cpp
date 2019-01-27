#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> field;

int solve() {
	int dif = 0;

	for (int i = 0; i < field.size(); i++) {
		int last = -1;
		for (int j = 0; j < field.size(); j++) {
			if (field.at(i).at(j) >= 0) {
				if (last != -1) {
					dif = std::max(dif, abs(field.at(i).at(j) - field.at(i).at(last)) - (j - last));
				} 
				last = j;
			}
		}
	}

	for (int i = 0; i < field.size(); i++) {
		int last = -1;
		for (int j = 0; j < field.size(); j++) {
			if (field.at(j).at(i) >= 0) {
				if (last != -1) {
					dif = std::max(dif, abs(field.at(j).at(i) - field.at(last).at(i)) - (j - last));
				}
				last = j;
			}
		}
	}

	return dif;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int d, x, y, s;
		cin >> d >> x >> y >> s;

		field = vector<vector<int>>(d, vector<int>(d, -1));
		int dist = 0;
		field[x][y] = dist;
		for (int j = 0; j < s; j++) {
			dist++;
			
			int q;
			cin >> q;
			if (q == 1) x--;
			if (q == 2) x++;
			if (q == 3) y--;
			if (q == 4) y++;

			field[x][y] = dist;
		}

		int sol = solve();
		if (sol == 0) cout << i << " geen sluipweg" << endl;
		else cout << i << " " << (dist - sol) << endl;
	}
}
