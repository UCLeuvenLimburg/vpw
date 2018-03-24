#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> find_solutions(string fout, string correct, unsigned index, unsigned max, string current) {
	if (fout == correct) {
		vector<string> result;
		result.push_back(current);
		return result;
	}
	if (current.size() / 2 >= max) {
		return vector<string>();
	}

	vector<string> solutions;

	for (unsigned i = index; i < fout.size(); i++) {
		if (fout.at(i) != correct.at(i)) {

			for (unsigned j = i + 1; j < correct.size(); j++) {
				if (fout.at(j) != correct.at(j)) {

					if (fout.at(i) == correct.at(j) || fout.at(j) == correct.at(i)) {
						string cycle(2, 'A');
						cycle.at(0) += i;
						cycle.at(1) += j;

						string s(fout);
						swap(s.at(i), s.at(j));

						vector<string> result = find_solutions(s, correct, i, max, current + cycle);
						solutions.insert(solutions.end(), result.begin(), result.end());
					}

				}
			}

		}
	}

	return solutions;
}

void find_switch(string& fout, string& correct) {
	//Switch die 2 tekens tegelijk juist plaatst, krijgt voorrang
	for (unsigned i = 0; i < fout.size(); i++) {
		if (fout.at(i) != correct.at(i)) {

			for (unsigned j = i + 1; j < correct.size(); j++) {
				if (fout.at(j) != correct.at(j)) {

					if (fout.at(i) == correct.at(j) && fout.at(j) == correct.at(i)) {
						swap(fout.at(i), fout.at(j));
						return;
					}

				}
			}

		}
	}

	//zoek switch die maar 1 teken juist zet
	for (unsigned i = 0; i < fout.size(); i++) {
		if (fout.at(i) != correct.at(i)) {

			for (unsigned j = i + 1; j < correct.size(); j++) {
				if (fout.at(j) != correct.at(j)) {

					if (fout.at(i) == correct.at(j) || fout.at(j) == correct.at(i)) {
						swap(fout.at(i), fout.at(j));
						return;
					}

				}
			}

		}
	}
}

//Tel het maximaal aantal switches
unsigned count_switches(string fout, string correct) {
	unsigned count = 0;

	while (fout != correct) {
		find_switch(fout, correct);
		count++;
	}

	return count;
}

string solve(string fout, string correct) {
	unsigned max_switches = count_switches(fout, correct);							//Bereken het maximaal aantal switches nodig
	vector<string> solutions = find_solutions(fout, correct, 0, max_switches, "");	//Vind alle mogelijk oplossingen
	return *min_element(solutions.begin(), solutions.end());						//Neem het alfabetisch eerste
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string fout;
		string correct;

		cin >> fout;
		cin >> correct;

		cout << i;
		if (fout == correct) {
			cout << " correct" << endl;
		}
		else if (count(fout.begin(), fout.end(), 'L') != count(correct.begin(), correct.end(), 'L')
			|| count(fout.begin(), fout.end(), 'R') != count(correct.begin(), correct.end(), 'R')
			|| count(fout.begin(), fout.end(), 'S') != count(correct.begin(), correct.end(), 'S')) {
			cout << " onmogelijk" << endl;
		}
		else {
			cout << " " << solve(fout, correct) << endl;
		}
	}

	return 0;
}
