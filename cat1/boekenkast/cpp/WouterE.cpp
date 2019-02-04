#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int r;
		cin >> r;

		vector<int> rekken(r, 0);
		for (int j = 0; j < r; j++) cin >> rekken.at(j);

		int b;
		cin >> b;

		vector<pair<string, int>> boeken(b, { "", 0 });
		for (int j = 0; j < b; j++) getline(cin >> boeken.at(j).second, boeken.at(j).first);

		sort(rekken.rbegin(), rekken.rend());
		sort(boeken.begin(), boeken.end());

		int boek_index = 0, rek_index = 0;
		while (rek_index < rekken.size() && boek_index < boeken.size()) {
			while (boek_index < boeken.size() && boeken.at(boek_index).second <= rekken.at(rek_index)) {
				rekken.at(rek_index) -= boeken.at(boek_index).second;
				boek_index++;
			}
			rek_index++;
		}

		if (boek_index < boeken.size()) {
			cout << i << " ONMOGELIJK" << endl;
		}
		else {
			cout << i << " " << rek_index << endl;
		}
	}
}
