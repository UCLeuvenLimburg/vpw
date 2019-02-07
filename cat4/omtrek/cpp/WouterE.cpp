#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct obj { int x, y, dx, dy; };

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int r, max = 0;
		cin >> r;

		vector<obj> rechthoek(r);
		for (int j = 0; j < r; j++) {
			cin >> rechthoek.at(j).x >> rechthoek.at(j).y >> rechthoek.at(j).dx >> rechthoek.at(j).dy;
			max = std::max(max, rechthoek.at(j).x + rechthoek.at(j).dx);
			max = std::max(max, rechthoek.at(j).y + rechthoek.at(j).dy);
		}

		vector<vector<bool>> veld(max + 4, vector<bool>(max + 4, false));
		for (obj o : rechthoek) {
			for (int a = o.x; a < o.x + o.dx; a++) {
				for (int b = o.y; b < o.y + o.dy; b++) {
					veld.at(a + 2).at(b + 2) = true;
				}
			}
		}

		int omtrek = 0, oppervlak = 0;

		for (int a = 1; a < max + 3; a++) {
			for (int b = 1; b < max + 3; b++) {
				if (veld.at(a).at(b)) {
					oppervlak++;
				}
				else {
					omtrek += veld.at(a + 1).at(b);
					omtrek += veld.at(a - 1).at(b);
					omtrek += veld.at(a).at(b + 1);
					omtrek += veld.at(a).at(b - 1);
				}
			}
		}

		cout << i << " " << oppervlak << " " << omtrek << endl;
	}
}
