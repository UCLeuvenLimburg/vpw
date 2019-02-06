#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int s;
		cin >> s;

		int x = 0, y = 0;
		for (int j = 0; j < s; j++) {
			char c;
			cin >> c;
			if (c == 'N') y++;
			if (c == 'Z') y--;
			if (c == 'O') x++;
			if (c == 'W') x--;
		}

		cout << i << " " << x << " " << y << endl;
	}
}
