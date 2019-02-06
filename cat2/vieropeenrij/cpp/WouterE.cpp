#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int g, c;
		cin >> g >> c;

		vector<vector<char>> bord(g, vector<char>(g, '.'));
		for (int j = 0; j < c; j++) {
			int x, y = 0;
			cin >> x;
			x--;
			while (y < g - 1 && bord.at(y + 1).at(x) == '.') y++;
			bord.at(y).at(x) = j % 2 == 0 ? 'R' : 'G';
		}

		vector<vector<char>> new_bord(g, vector<char>(g, '.'));
		for (int x = 0; x < g; x++) {
			int y = g - 1;
			int index = g - 1;
			while (index >= 0) {
				while (index >= 0 && bord.at(x).at(index) == '.') index--;
				if (index >= 0) new_bord.at(y--).at(g - x - 1) = bord.at(x).at(index--);
			}
		}

		for (auto v : new_bord) {
			cout << i << " ";
			for (char c : v) {
				cout << c;
			}
			cout << endl;
		}
	}
}
