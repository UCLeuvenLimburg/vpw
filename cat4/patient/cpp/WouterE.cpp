#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vvb = vector<vb>;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ds;
		cin >> ds;

		vvi docters;
		for (int j = 0; j < ds; j++) {
			int as;
			cin >> as;

			docters.push_back(vi());
			for (int k = 0; k < as; k++) {
				int a;
				cin >> a;
				docters.at(j).push_back(a);
			}
		}

		int ps;
		cin >> ps;

		vi patient;
		for (int j = 0; j < ps; j++) {
			int p;
			cin >> p;
			patient.push_back(p);
		}

		vvb bits;
		for (auto d : docters) {
			bits.push_back(vb(patient.size(), false));

			for (auto dd : d) {
				auto it = find(patient.begin(), patient.end(), dd);
				if (it != patient.end()) {
					bits.back().at(it - patient.begin()) = true;
				}
			}
		}

		cout << i << " " << (max_element(bits.begin(), bits.end()) - bits.begin() + 1) << endl;;
	}
}
