#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct pos { int x, y; };

vector<vector<int>> field;
int target;

pos find(int value) {
	for (int i = 0; i < field.size(); i++) {
		for (int j = 0; j < field.at(0).size(); j++) {
			if (field[i][j] == value) return { i, j };
		}
	}
	return { -1, -1 };
}

bool around(pos p1, pos p2) {
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);
	return dx <= 1 && dy <= 1;
}

bool solve(pos p, int current) {
	if (current > target) return true;

	pos cp = find(current);
	if (cp.x != -1) return (p.x == -1 || around(p, cp)) && solve(cp, current + 1);

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			int nx = p.x + dx;
			int ny = p.y + dy;
			if (nx >= 0 && nx < field.size() && ny >= 0 && ny < field.at(0).size() && field[nx][ny] == 0) {
				field[nx][ny] = current;
				if (solve({ nx, ny }, current + 1)) return true;
				field[nx][ny] = 0;
			}
		}
	}

	return false;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h;
		cin >> b >> h;

		field = vector<vector<int>>(b, vector<int>(h, -1));
		target = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				string s;
				cin >> s;

				if (s == ".") { 
					field[x][y] = 0;
					target++;
				}
				else if (s == "x") {
					field[x][y] = -1;
				}
				else {
					field[x][y] = stoi(s);
					target++;
				}
			}
		}

		solve({ -1, -1 }, 1);

		for (int y = 0; y < h; y++) {
			cout << i;
			for (int x = 0; x < b; x++) {
				cout << " " << (field[x][y] == -1 ? "x" : to_string(field[x][y]));
			}
			cout << endl;
		}
	}
}
