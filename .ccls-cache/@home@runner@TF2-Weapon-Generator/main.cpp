#include "weapon.hpp" //also includes stats.hpp, data.hpp, <array>, <cmath>, <string>, <vector>, & namespace:std
//#include <algorithm>
using namespace std;

int main() {
	cout << "Hello World!"; //just because
	/*//Testing stuff
	string arr [4][3] {
		{"first","second","third"},
		{"first","second"},
		{"first"}
	};
	cout << "\nsizeof(arr) = " << sizeof(arr);
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		cout << "\nsizeof(arr[" << i << "]) = " << sizeof(arr[i]);
		for (int j = 0; j < sizeof(arr[0]) / sizeof(arr[i][0]); j++) {
			cout << "\nsizeof(arr[" << i << "][" << j << "]) = " << sizeof(arr[i][j]);
			cout << "\narr[" << i << "][" << j << "] = " << arr[i][j];
		}
		cout << endl;
	}
	//Generator Code*/
	int zeroPos = versionFull.find("0", versionFull.find("."));
	while (zeroPos != string::npos) {
		versionFull.erase(zeroPos, 1);
		zeroPos = versionFull.find("0", versionFull.find("."));
	};
	string tempString = "Sunny's TF2 Weapon Generator v." + versionFull;
	cout << lineBreak(tempString) << tempString << lineBreak(tempString);
	/*cout << "Enter seed or leave blank: \n"
	cin >> userSeed; */
	vector<Wep> weapons;
	int curWepNum = -1;
	vector<string> paramaters(9);
	vector<array<int, 2>> customCoords;
	bool skip = false;
	int upsideNum = 2;
	while (0 == 0) {
		if (skip == false) {
			cout << "How many upsides would you like to generate (an undefined amount of downsides will be generated to balance the upsides until the weapon is balanced). Note: type \"skip\" to skip all messages for the rest of the session: ";
			getline(cin, tempString);
			transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
			if (tempString == "skip") {
				skip = true;
				fill(paramaters.begin(), paramaters.end(), "-1");
				goto wepGeneration;
			} else {
				try {
					upsideNum = stoi(tempString);
				} catch (const std::invalid_argument& ia) {
			  	cout << "Invalid argument: " << ia.what() << "Result defaulted to \'2\'\n";
					upsideNum = 2;
		  	}
			}
			paramaters[0] = to_string(upsideNum); //this is kinda useless but whatevs
			cout << "Randomly generate or customize / manually select weapons / stats? (1 for customize, anything else for random): ";
			getline(cin, tempString);
			cout << tempString;
			if (tempString[0] == '1') {
				cout << "\nnote: leave feild blank to have the value randomly generated. \nChoose a weapon type OR weapon slot (generated weapon will be in selected slot): ";
				getline(cin, tempString);
				if (cin.gcount() == 0 || find(begin(weaponList), end(weaponList), tempString) == end(weaponList) && find(begin(weaponSlots), end(weaponSlots), tempString) == end(weaponSlots)) {
					paramaters[1] = "";
					paramaters[2] = "";
				} else if (find(begin(weaponSlots), end(weaponSlots), tempString) == end(weaponSlots)) {
					paramaters[1] = tempString;
					paramaters[2] = "";
				} else {
					paramaters[1] = "";
					paramaters[2] = tempString;
				}
				cout << "\nChoose custom stat coordinates? (y/n): ";
				getline(cin, tempString);
				if (tempString[0] == 'y') {
					//for (int i = 0; i < upsideNum; i++) {
						cout << "coming soon lol\n";
					//}
				}
				cout << "\nAre these weapon's stats only when active? (y/n): "; 
				getline(cin, tempString);
				if (tempString[0] == 'y') {
					paramaters[3] = "0";
				} else {
					paramaters[3] = "1";
				}
				cout << "\nDoes this weapon have a meter (Only works if weapon does not already have a meter and if meters are allowed)? (y/n): "; 
				getline(cin, tempString);
				if (tempString[0] == 'y') {
					paramaters[4] = "0";
				} else {
					paramaters[4] = "1";
				}
				cout << "\nBypass stat rating? (there will instead be an equal amount of upsides & downsides; y/n)"; 
				getline(cin, tempString);
				if (tempString[0] == 'y') {
					paramaters[6] = "0";
				} else {
					paramaters[6] = "1";
				}
				cout << "\nBypass blacklist and dupe stat sheck? (stupidity may ensue; y/n): "; 
				getline(cin, tempString);
				if (tempString[0] == 'y') {
					paramaters[7] = "0";
				} else {
					paramaters[7] = "1";
				}
				cout << "\nEnable Debug?; y/n): "; 
				getline(cin, tempString);
				if (tempString[0] == 'y') {
					paramaters[5] = "0";
				} else {
					paramaters[5] = "1";
				}
			}
		}
		wepGeneration:
		for (int i = 0; i < paramaters.size(); i++) {
			cout << "paramaters[\"" << i << "\"] = " << paramaters[i] << endl;
		}
		int arr[2] = {stoi(paramaters[3]), stoi(paramaters[4])};
		bool a = true;
		if (stoi(paramaters[5]) == 1) {
			a = false;
		}
		bool b = false;
		if (stoi(paramaters[6]) == 0) {
			b = true;
		}
		bool c = false;
		if (stoi(paramaters[7]) == 0) {
			c = true;
		}
		int arrPlaceholder[1][2] = {{-1,-1}};
		weapons.emplace_back(upsideNum, paramaters[1], paramaters[2], arrPlaceholder, arr, a, b, c);
		//int num, string preDefWepSlot, string preDefWepType, int preDefCoords[][2], int preDefProperties[], bool ps, bool debug, bool bypassRating, bool bypassBlacklist
		curWepNum++;
		weapons[curWepNum].printStats(true);
		cout << "press ENTER to continue\n";
		cin.ignore();
	}
}