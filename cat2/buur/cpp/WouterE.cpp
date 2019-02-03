#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h;
		cin >> b >> h;

		vector<vector<char>> kaart(h, vector<char>(b, '0'));
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				cin >> kaart.at(j).at(k);
			}
		}

		map<char, set<char>> neighbours;
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				if (j > 0) neighbours[kaart.at(j).at(k)].insert(kaart.at(j - 1).at(k));
				if (k > 0) neighbours[kaart.at(j).at(k)].insert(kaart.at(j).at(k - 1));
				if (j < h - 1) neighbours[kaart.at(j).at(k)].insert(kaart.at(j + 1).at(k));
				if (k < b - 1) neighbours[kaart.at(j).at(k)].insert(kaart.at(j).at(k + 1));
			}
		}

		for (auto& p : neighbours) p.second.erase(p.first);

		for (int j = 0; j < h; j++) {
			cout << i;
			for (int k = 0; k < b; k++) {
				cout << " " << neighbours.at(kaart.at(j).at(k)).size();
			}
			cout << endl;
		}
	}
}
