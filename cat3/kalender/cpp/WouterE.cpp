#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ps, ds, l;
		cin >> ps >> ds >> l;

		vector<string> data(ps);
		for (int j = 0; j < ps; j++) cin >> data[j];

		vector<bool> merge(ds);
		for (int j = 0; j < ds; j++) merge[j] = all_of(data.begin(), data.end(), [j](const string& s) { return s[j] == 'V'; });

		int result = -1;
		int offset = find(merge.begin(), merge.end(), true) - merge.begin();
		while (result == -1 && offset < ds) {
			int next = find(merge.begin() + offset, merge.end(), false) - merge.begin();
			if (next - offset >= l) result = offset;
			offset = find(merge.begin() + next, merge.end(), true) - merge.begin();
		}

		if (result == -1) cout << "X" << endl;
		else cout << (result + 1) << endl;
	}
}
