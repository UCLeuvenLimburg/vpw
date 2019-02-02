#include <iostream>
#include <vector>
#include <string>

using namespace std;

string solve(const vector<double>& temps) {
	int start = 0, count30 = 0;
	bool hittegolf = false;

	for (int index = 0; index < temps.size();) {
		double tmp = temps.at(index++);

		if (tmp < 25.0) {
			if (hittegolf) return to_string(start + 1) + " " + to_string(index - start - 1);
			start = index;
			count30 = 0;
		}
		else if (tmp > 30.0) {
			count30++;
		}

		if (index - start >= 5 && count30 >= 3) {
			hittegolf = true;
		}
	}

	if (hittegolf) return to_string(start + 1) + " " + to_string(temps.size() - start - 1);
	else return "geen hittegolf";
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		vector<double> temps;
		
		string str;
		cin >> str;
		while (str != "stop") {
			temps.push_back(stod(str));
			cin >> str;
		}

		cout << i << " " << solve(temps) << endl;
	}
}
