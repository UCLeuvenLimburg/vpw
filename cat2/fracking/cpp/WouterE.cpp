#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> field;
vector<vector<bool>> tmp;

bool stable(int x, int y) {
	if (y == tmp.at(0).size()) return true;
	if (x < 0 || x >= tmp.size() || y < 0 || y >= tmp.at(0).size() || !tmp[x][y]) return false;
	tmp[x][y] = false;
	return stable(x + 1, y) || stable(x - 1, y) || stable(x, y - 1) || stable(x, y + 1);
}

bool stable() {
	tmp = field;
	for (int i = 0; i < field.size(); i++) {
		if (stable(i, 0)) return true;
	}
	return false;
}

void fracking() {
	tmp = field;
	
	for (int i = 0; i < field.size(); i++) {
		for (int j = 0; j < field.at(0).size(); j++) {
			field[i][j] = !(
				(i > 0 && !tmp[i - 1][j]) ||
				(i < field.size() - 1 && !tmp[i + 1][j]) ||
				(j > 0 && !tmp[i][j - 1]) ||
				(j < field.at(0).size() - 1 && !tmp[i][j + 1]));
		}
	}

}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int h, b;
		cin >> h >> b;

		field = vector<vector<bool>>(b, vector<bool>(h, false));
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				char c;
				cin >> c;
				field[k][j] = c == '*';
			}
		}

		int sol = 0;
		while (stable()) {
			sol++;
			fracking();
		}
		
		cout << i << " " << sol << endl;
	}
}
