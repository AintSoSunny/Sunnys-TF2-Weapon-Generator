#include "weapon.hpp" //also includes stats.hpp, data.hpp, <array>, <cmath>, <string>, <vector>, & namespace:std
//#include <algorithm>
using namespace std;

int main() {
	cout << "Hello, World!\n\n";
	/*cout << "Enter seed or leave blank: \n"
	cin >> userSeed; */
	Wep weapon(2);
	weapon.printStats(true);
	/*vector<int> n(1000);
	for (int i = 0; i < 1000; i++) {
		srand(i);
		int j = rand() % 29 - 8;
		if (j < 0) {
			j *= -1;
		}
		if (j <= 7) {
			j += 2;
		}
		n.push_back(j);
	}
	for (int i = 0; i < 21; i++) {
		cout << i << ": " << count(n.begin(), n.end(), i) << endl;
	}*/
}