#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string line;
		getline(cin, line); 
		getline(cin, line);

		int steps;
		cin >> steps;

		for (int j = 0; j < steps; j++) {
			string next = line;
			for (int k = 0; k < line.size(); k++) {
				next.at(k) = line.at(max(k - 1, 0)) != line.at(min(k + 1, (int)line.size() - 1)) ? '1' : '0';
			}
			line = next;
		}

		cout << line << endl;
	}
}
