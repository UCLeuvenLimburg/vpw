#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string rang[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "B", "V", "H" };
char color[4] = { 'K', 'R', 'H', 'S' };

int rang_of(string s) {
	return find(rang, rang + 13, s.substr(1)) - rang;
}

int color_of(string s) {
	return find(color, color + 4, s.at(0)) - color;
}

int solve(string l, string m, string r) {
	int r1 = rang_of(l) * 4 + color_of(l);
	int r2 = rang_of(m) * 4 + color_of(m);
	int r3 = rang_of(r) * 4 + color_of(r);

	if (r1 < r2) {
		if (r2 < r3) return 1;
		else if (r1 < r3) return 2;
		else return 4;
	}
	else {
		if (r1 < r3) return 3;
		else if (r2 < r3) return 5;
		else return 6;
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string k1, k2, k3, k4;
		cin >> k1 >> k2 >> k3 >> k4;

		char k = k1.at(0);
		string r = rang[(rang_of(k1) + solve(k2, k3, k4)) % 13];
		cout << i << " " << k << r << endl;
	}
}
