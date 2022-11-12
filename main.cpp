#include "weapon.hpp" //also includes stats.hpp, data.hpp, <array>, <cmath>, <string>, <vector>, & namespace:std
//#include <algorithm>
using namespace std;

int main() {
	cout << "Hello World!";//just because
	/*
	array<int,2> arr1 = {1,2};
	array<int,2> arr2 = {1,2};
	array<int,2> arr3 = {3,4};
	array<array<int,2>,2> multiArr = {{{1,2}, {3,4}}};
	cout << "\nTrial 1: ";
	if (arr1 == arr2) {cout << "True.\n";} else {cout << "Not True.\n";}
	cout << "Trial 2: ";
	if (arr1 == array<int,2>({1,2})) {cout << "True.\n";} else {cout << "Not True.\n";}
	cout << "Trial 3: ";
	if (arr1 == arr3) {cout << "True.\n";} else {cout << "Not True.\n";}
	cout << "Trial 4: ";
	if (arr1 == multiArr[0]) {cout << "True.\n";} else {cout << "Not True.\n";}
	cout << "Trial 5: ";
	if (multiArr[0] == array<int,2>({1,2})) {cout << "True.\n";} else {cout << "Not True.\n";}
	cout << "Trial 6: ";
	if (multiArr == array<array<int,2>,2>({{{1,2}, {3,4}}})) {cout << "True.\n";} else {cout << "Not True.\n";}
	cout << "Trial 7: ";
	if (arr3 == multiArr.back()) {cout << "True.\n";} else {cout << "Not True.\n";}
	*/
	//Generator Code
	int zeroPos = versionFull.find("0", versionFull.find("."));
	while (zeroPos != string::npos) {
		versionFull.erase(zeroPos, 1);
		zeroPos = versionFull.find("0", versionFull.find("."));
	};
	string tempString = "Sunny's TF2 Weapon Generator v." + versionFull;
	cout << lineBreak(tempString) << tempString << lineBreak(tempString);
	//cout << "Enter seed or leave blank: \n"; cin >> userSeed; 
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
			cout << "Manually select weapons / stats? (Press ENTER to repeat previous inputs; y/n): ";
			getline(cin, tempString);
			cout << tempString;
			if (tolower(tempString[0]) == 'y') {
				cout << "\nNote: leave feild blank to have the value set to default or randomly generated. \nChoose a weapon type OR weapon slot (generated weapon will be in selected slot): ";
				getline(cin, tempString);
				tempString[0] = toupper(tempString[0]);
				if (find(begin(weaponSlots), end(weaponSlots), tempString) != end(weaponSlots)) {
					paramaters[1] = tempString;
					paramaters[2] = "";
				} else if (find(begin(weaponList), end(weaponList), tempString) != end(weaponList)) {
					paramaters[1] = "";
					paramaters[2] = tempString;
				}
				cout << "\nChoose custom stat coordinates? (y/n): ";
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					//for (int i = 0; i < upsideNum; i++) {
						cout << "coming soon lol\n";
					//}
				}
				cout << "\nAre these weapon's stats only when active? (y/n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
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
				cout << "\nBypass stat rating? (there will instead be an equal amount of upsides & downsides; y/n; DEFAULT: n)"; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[6] = "0";
				} else {
					paramaters[6] = "1";
				}
				cout << "\nBypass blacklist and dupe stat sheck? (stupidity may ensue; y/n; DEFAULT: n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[7] = "0";
				} else {
					paramaters[7] = "1";
				}
				cout << "\nEnable Debug? (y/n; DEFAULT: y): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[5] = "0";
				} else {
					paramaters[5] = "1";
				}
			} else if (tolower(tempString[0]) == 'n') {
				fill(paramaters.begin(), paramaters.end(), "-1");
				paramaters[0] = to_string(upsideNum);
			}
		}
		wepGeneration:
		for (int i = 0; i < paramaters.size(); i++) {
			if (i > 2 && paramaters[i] == "") {
				paramaters[i] = "-1";
			}
			cout << "paramaters[" << i << "] = \"" << paramaters[i] << "\"\n";
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