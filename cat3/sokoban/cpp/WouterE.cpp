#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum vakje { Leeg, Muur, Doel };
enum actor { Vrij, Blok };

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int r, c;
		string line;
		cin >> r >> c;
		getline(cin, line);

		int sx = -1, sy = -1;
		vector<vector<vakje>> veld(r, vector<vakje>(c, Leeg));
		vector<vector<actor>> blok(r, vector<actor>(c, Vrij));
		for (int j = 0; j < r; j++) {
			getline(cin, line);
			for (int k = 0; k < c; k++) {
				char cc = line.at(k);

				if (cc == '#') veld.at(j).at(k) = Muur;
				if (cc == '+' || cc == '*' || cc == '.') veld.at(j).at(k) = Doel;
				if (cc == '+' || cc == '@') sy = j, sx = k;
				if (cc == '*' || cc == '$') blok.at(j).at(k) = Blok;
			}
		}

		int cs;
		cin >> cs;
		getline(cin, line);
		getline(cin, line);

		for (int j = 0; j < cs; j++) {
			char cc = line.at(j);

			int dx = 0, dy = 0;
			if (cc == 'L') dx = -1;
			if (cc == 'R') dx = 1;
			if (cc == 'B') dy = -1;
			if (cc == 'O') dy = 1;

			int nx = sx + dx, ny = sy + dy;
			if (veld.at(ny).at(nx) != Muur) {
				if (blok.at(ny).at(nx) == Blok && blok.at(ny + dy).at(nx + dx) == Vrij && veld.at(ny + dy).at(nx + dx) != Muur) {
					blok.at(ny).at(nx) = Vrij;
					blok.at(ny + dy).at(nx + dx) = Blok;
					sx = nx, sy = ny;
				}
				else if (blok.at(ny).at(nx) == Vrij) {
					sx = nx, sy = ny;
				}
			}
		}

		for (int j = 0; j < r; j++) {
			for (int k = 0; k < c; k++) {
				if (veld.at(j).at(k) == Leeg) {
					if (sx == k && sy == j) cout << "@";
					else if (blok.at(j).at(k) == Blok) cout << "$";
					else if (blok.at(j).at(k) == Vrij) cout << " ";
				}
				else if (veld.at(j).at(k) == Doel) {
					if (sx == k && sy == j) cout << "+";
					else if (blok.at(j).at(k) == Blok) cout << "*";
					else if (blok.at(j).at(k) == Vrij) cout << ".";
				}
				else if (veld.at(j).at(k) == Muur) {
					cout << "#";
				}
			}
			cout << endl;
		}
		if(i < n) cout << endl;
	}
}
