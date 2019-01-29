#include <iostream>
#include <string>
#include <map>

using namespace std;

string solve(map<string, string> data, string scan) {
	int index = 0;
	string result = "";

	while (index < scan.size()) {
		int length = scan.size() - index;
		while (length > 0 && data.find(scan.substr(index, length)) == data.end()) {
			length--;
		}

		if (length == 0) return "ONMOGELIJK";
		result += data.at(scan.substr(index, length));
		index += length;
	}

	return result;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string scan;
		cin >> scan;

		int ss;
		cin >> ss;

		map<string, string> data;
		for (int j = 0; j < ss; j++) {
			string d, key;
			cin >> d >> key;
			data[key] = d;
		}

		cout << i << " " << solve(data, scan) << endl;
	}
}
