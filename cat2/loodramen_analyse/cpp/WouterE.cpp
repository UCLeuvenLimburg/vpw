#include <iostream>
#include <vector>

using namespace std;

int r, k;
vector<vector<bool>> raam;

void solve(int x1, int y1, int x2, int y2) {
	int sx = x1 + 1, sy = y1 + 1;
	while (sx < x2 && !(raam.at(sx).at(y1) && raam.at(sx).at(y2))) sx++;
	while (sy < y2 && !(raam.at(x1).at(sy) && raam.at(x2).at(sy))) sy++;
	if (sx >= x2 || sy >= y2) return;

	cout << "(" << (sx + 1) << "," << (sy + 1) << ")";
	cout << "["; solve(x1, y1, sx - 1, sy - 1); cout << "]";
	cout << "["; solve(x1, sy + 1, sx - 1, y2); cout << "]";
	cout << "["; solve(sx + 1, y1, x2, sy - 1); cout << "]";
	cout << "["; solve(sx + 1, sy + 1, x2, y2); cout << "]";
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> r >> k;

		raam = vector<vector<bool>>(r, vector<bool>(k, false));
		for (int y = 0; y < r; y++) {
			for (int x = 0; x < k; x++) {
				char c;
				cin >> c;
				raam.at(y).at(x) = c == '*';
			}
		}

		cout << i << " " << "<" << r << "," << k << ">";
		solve(0, 0, r - 1, k - 1);
		cout << endl;
	}
}
