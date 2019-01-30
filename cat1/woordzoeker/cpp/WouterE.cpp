#include <iostream>
#include <vector>
#include <string>

using namespace std;

int a, r, k;
vector<string> woorden, veld;
vector<vector<bool>> used;

bool test(int x, int y, string str, int dx, int dy) {
	if (str == "") return true;
	if (x >= 0 && y >= 0 && x < k && y < r && 
		str.front() == veld.at(y).at(x) && 
		test(x + dx, y + dy, str.substr(1), dx, dy)) 
	{
		return used.at(y).at(x) = true;
	}

	return false;
}

void find(string woord) {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < r; j++) 
		{
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					if (dx != 0 || dy != 0) 
					{
						if (test(i, j, woord, dx, dy)) return;
					}
				}
			}
		}
	}
}

string solve() {
	used = vector<vector<bool>>(r, vector<bool>(k, false));
	for (string s : woorden) find(s);

	string result = "";
	for (int y = 0; y < r; y++) {
		for (int x = 0; x < k; x++) {
			if (!used.at(y).at(x)) {
				result += veld.at(y).at(x);
			}
		}
	}

	return result;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> a >> r >> k;

		woorden.clear();
		for (int j = 0; j < a; j++) {
			string x;
			cin >> x;
			woorden.push_back(x);
		}

		veld.clear();
		for (int j = 0; j < r; j++) {
			string x;
			cin >> x;
			veld.push_back(x);
		}

		cout << i << " " << solve() << endl;
	}
}
