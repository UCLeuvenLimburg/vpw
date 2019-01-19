#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int nrs;
		cin >> nrs;
		
		vector<int> getallen;
		int sum = 0;

		for (int k = 0; k < nrs; k++) {
			int x;
			cin >> x;
			sum += x;
			getallen.push_back(x);
		}

		if (sum % 3 == 0) {
			int target = sum / 3;
			int index = 0;
			int part_sum = 0;

			while (part_sum != target && index < getallen.size()) {
				part_sum += getallen.at(index++);
			}

			part_sum = 0;
			int possibilities = target == 0;
			int zero_reached = possibilities + 1;

			for (; index < getallen.size(); index++) {
				part_sum += getallen.at(index);
				
				if (part_sum == target) possibilities += zero_reached;
				if (part_sum == 0) zero_reached++;
			}

			cout << i << " " << possibilities << endl;
		}
		else {
			cout << i << " " << 0 << endl;
		}
	}
}
