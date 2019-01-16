#include <iostream>
#include <set>
#include <memory>
#include <queue>

using namespace std;

using ss = shared_ptr<set<int>>;
struct ii { int x, y; };

int land[500][500];
ss result[500][500];
int b, h;
int id;

void spread(int sx, int sy, int from, int to) {
	queue<ii> todo;
	todo.push({ sx, sy });

	while (!todo.empty()) {
		ii p = todo.front();
		todo.pop();

		if (p.x >= 0 && p.x < b && p.y >= 0 && p.y < h) {
			if (land[p.x][p.y] == from) {
				land[p.x][p.y] = to;
			
				todo.push({p.x - 1, p.y});
				todo.push({p.x + 1, p.y});
				todo.push({p.x, p.y - 1});
				todo.push({p.x, p.y + 1});
			}
		}
	}
}

void count(int sx, int sy, int id, ss neighbours) {
	queue<ii> todo;
	todo.push({ sx, sy });

	while (!todo.empty()) {
		ii p = todo.front();
		todo.pop();

		if (p.x >= 0 && p.x < b && p.y >= 0 && p.y < h) {
			if (land[p.x][p.y] == id && result[p.x][p.y] == nullptr) {
				result[p.x][p.y] = neighbours;

				todo.push({p.x - 1, p.y});
				todo.push({p.x + 1, p.y});
				todo.push({p.x, p.y - 1});
				todo.push({p.x, p.y + 1});
			}
			else if(land[p.x][p.y] != id){
				neighbours->insert(land[p.x][p.y]);
			}
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> b >> h;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				char c;
				cin >> c;
				land[x][y] = (int)c;

				result[x][y].reset();
			}
		}

		id = 256;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				if (land[x][y] < 256) {
					id++;
					spread(x, y, land[x][y], id);
				}
			}
		}

		for (int y = 0; y < h; y++) {
			cout << i;
			for (int x = 0; x < b; x++) {
				if (!result[x][y]) {
					count(x, y, land[x][y], make_shared<set<int>>());
				}

				cout << " " << result[x][y]->size();
			}
			cout << endl;
		}
	}
}
