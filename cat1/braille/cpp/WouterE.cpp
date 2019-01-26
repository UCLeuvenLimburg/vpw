#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	map<tuple<string, string, string>, char> letters;

	string data[3];
	getline(cin, data[0]);
	getline(cin, data[1]);
	getline(cin, data[2]);

	for (int i = 0; i < 26 * 2; i += 2) {
		letters[{
			data[0].substr(i, 2), 
			data[1].substr(i, 2), 
			data[2].substr(i, 2)}] = 'A' + i / 2;
	}

	int n;
	cin >> n;
	getline(cin, data[0]);

	for (int i = 1; i <= n; i++) {
		getline(cin, data[0]);
		getline(cin, data[1]);
		getline(cin, data[2]);

		cout << i << " ";
		for (int j = 0; j < data[0].size(); j += 2) {
			cout << letters.at({
				data[0].substr(j, 2),
				data[1].substr(j, 2),
				data[2].substr(j, 2)
			});
		}
		cout << endl;
	}
}
