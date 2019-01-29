#include <iostream>
#include <vector>

using namespace std;

bool losing(const vector<int>& field) {
	int nim_value = 0;
	bool end_game = true;

	for (int x : field) {
		nim_value ^= x;
		end_game &= x <= 1;
	}

	return (nim_value > 0) == end_game;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;

		vector<int> field;
		for (int j = 0; j < k; j++) {
			int x;
			cin >> x;
			field.push_back(x);
		}

		bool winning = false;
		for (int j = 0; j < k; j++) {
			for (int y = 0; y < field.at(j); y++) {
				vector<int> next = field;
				next.at(j) = y;

				if (losing(next)) {
					winning = true;

					cout << i;
					for (int z : next) {
						cout << " " << z;
					}
					cout << endl;
				}
			}
		}

		if (!winning) {
			cout << i << " HOPELOOS" << endl;
		}
	}
}