#include <iostream>
#include <vector>

using namespace std;

using dir = pair<int, int>;
using vp = vector<pair<dir, dir>>;

dir to_dir(char c) {
	if (c == 'N') return { 0, 1 };
	if (c == 'O') return { -1, 0 };
	if (c == 'Z') return { 0, -1 };
	return { 1, 0 };
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h;
		cin >> b >> h;

		vector<vp> veld(h, vp(b));
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				char c1, c2;
				cin >> c1 >> c2;
				veld.at(j).at(k) = { to_dir(c1), to_dir(c2) };
			}
		}

		int x = 0, y = 0;
		dir flow_dir = { 0, 1 };
		int water = 0;
		while (x >= 0 && y >= 0 && x < b && y < h && (veld.at(y).at(x).first == flow_dir || veld.at(y).at(x).second == flow_dir)) {
			if (veld.at(y).at(x).first == flow_dir) flow_dir = veld.at(y).at(x).second;
			else flow_dir = veld.at(y).at(x).first;

			x += (flow_dir.first *= -1);
			y += (flow_dir.second *= -1);
			water++;
		}

		cout << i << " " << water << endl;
	}
}
