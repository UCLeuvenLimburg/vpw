#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int h, b, c;
		cin >> h >> b >> c;
		
		vector<vector<bool>> raam(h, vector<bool>(b, false));
		for (int j = 0; j < c; j++) {
			int y, x;
			cin >> y >> x;

			--x, --y;
			for (int a = x; a < b && !raam.at(y).at(a); ++a) raam.at(y).at(a) = true;
			for (int a = y + 1; a < h && !raam.at(a).at(x); ++a) raam.at(a).at(x) = true;
			for (int a = x - 1; a >= 0 && !raam.at(y).at(a); --a) raam.at(y).at(a) = true;
			for (int a = y - 1; a >= 0 && !raam.at(a).at(x); --a) raam.at(a).at(x) = true;
		}

		for (auto v : raam) {
			cout << i << " ";
			for (bool b : v) {
				cout << (b ? '*' : '.');
			}
			cout << endl;
		}
	}
}
