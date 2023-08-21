#include "weapon.hpp" //also includes stats.hpp, data.hpp, <array>, <cmath>, <string>, <vector>, & namespace:std
//#include <algorithm>
using namespace std;
int main() {
	int tempInt;
	cout << "Hello World!";//just because
	//test shit
	/*
	unsigned int testSeed = (unsigned) time(NULL); 
	cout << "\n\nSeed A #1: " << testSeed;
	srand(testSeed);
	for (int i = 0; i < 51; i++) {
		cout << "\nRNG A #" << i << ": " << (rand() % 10);
	};
	for (int i = 0; i < 5; i++) {
		testSeed = (unsigned) (time(NULL) * i) % (unsigned int) pow(10,6); 
		cout << "\n\nSeed B #" << i << ": " << testSeed;
		srand(testSeed);
		for (int j = 0; j < 10; j++) {
			cout << "\nRNG B #" << j + 10*i << ": " << (rand() % 10);
		}
	}
	for (int i = 0; i < 12; i++) {
		testSeed = (unsigned) (time(NULL) * i) % 10000;
		cout << "\n\nSeed C #" << i << ": " << testSeed;
		srand(testSeed);
		for (int j = 0; j < 4; j++) {
			cout << "\nRNG C #" << j + 4*i << ": " << (rand() % 10);
		}
	}
	for (int i = 0; i < 51; i++) {
		testSeed = (unsigned) (time(NULL) * i) % 1000;
		srand(testSeed);
		cout << "\n\nSeed D #" << i << ": " << testSeed;
		cout << "\nRNG D #" << i << ": " << (rand() % 10);
	};
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
	array<int,16> paramaters;
	paramaters.fill(-1);
	vector<array<int,3>> statData;
	bool skip = false;
	int modMax = 20;
	while (0 == 0) {
		if (skip == false) {
			cout << "How many upsides (minimum) would you like to generate (an undefined amount of downsides will be generated to balance the upsides until the weapon is balanced. This also will not affect some weapons).\nNote: type \"skip\" to skip all messages for the rest of the session: ";
			getline(cin, tempString);
			transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
			if (tempString == "skip") {
				skip = true;
				goto wepGeneration;
			} else {
				tempString.erase(tempString.begin(), remove_if(tempString.begin(), tempString.end(), ::isdigit));
				try {
					paramaters[0] = stoi(tempString);
				} catch (const std::invalid_argument& ia) {
			  	cout << "Invalid argument: Input is not a valid number. Result defaulted to \'2\'\n";
					paramaters[0] = 2;
		  	}
			}
			cout << "Manually select weapons / stats? (Press ENTER to repeat previous inputs; y/n): ";
			getline(cin, tempString);
			cout << tempString;
			if (tolower(tempString[0]) == 'y') {
				cout << "\nNote: leave feild blank to have the value set to default or randomly generated. \nChoose a specific weapon type, weapon slot, and / or class (use commas to seperate entries): ";
				getline(cin, tempString);
				tempString += ",";
				tempInt = tempString.find(',');
				vector<string> wepData;
				do {
					cout << ".";
					wepData.push_back(tempString.substr(0, tempInt));
					tempString.erase(0, tempInt + 1);
					wepData.back()[0] = toupper(wepData.back()[0]);
					cout << "tempString = \"" << tempString << "\"; wepData.back() = \"" << wepData.back() << "\"\n";
					for (int i = 0; i < wepData.back().length(); i++) {
						if (isblank(wepData.back()[i])) {
							cout << "space...";
							if (i == wepData.back().length() - 1 || i == 0) {
								cout << "...i = " << i << "; wepData.back()[" << i << "] = '" << wepData.back()[i] << "'\n";
								wepData.back().erase(i, 1);
								i--;
							} //removes padding spaces
							wepData.back()[i + 1] = toupper(wepData.back()[i + 1]);
							cout << "wepData.back() = \"" << wepData.back() << "\"\n";
						}
					}
					tempInt = tempString.find(',');
					//cin.ignore();
				} while (tempInt != string::npos);
				for (int i = 0; i < wepData.size(); i++) {
					if (isdigit(wepData[i][0])) { //checks if first char is a digit
						tempString.erase(remove_if(tempString.begin(), tempString.end(), isInputSetInt), tempString.end());  
						tempInt = stoi(wepData[i]);
						if (tempInt > -1) {
							if (tempInt < weaponList.size() && paramaters[2] == -1) {
								paramaters[1] = tempInt;
							} else if (tempInt < weaponSlots.size() && paramaters[3] == -1) {
								paramaters[2] = tempInt;
							} else if (tempInt < classList.size() && paramaters[4] == -1) {
								paramaters[3] = tempInt;
							}
						}
					} else {
						cout << "wordEntry; wepData[" << i << "] = \"" << wepData[i] << "\"; detected as... ";
						tempInt = distance(weaponList.begin(), find(weaponList.begin(), weaponList.end(), wepData[i]));
						if (tempInt < weaponList.size()) {
							cout << "weapon\n";
							paramaters[1] = tempInt;
						} else {
							tempInt = distance(classList.begin(), find(classList.begin(), classList.end(), wepData[i]));
							if (tempInt < classList.size()) {
								cout << "class\n";
								paramaters[3] = tempInt;
							} else {
								tempString = wepData[i];
								transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
								cout << "tempString = \"" << tempString << "\"\n";
								tempInt = distance(weaponSlots.begin(), find(weaponSlots.begin(), weaponSlots.end(), tempString));
								if (tempInt < 4) {
									cout << "weapon slot\n";
									paramaters[2] = tempInt;
								} else {
									cout << "nothing... entry discarded\n";
								}
							}
						}
					}
				}
				cout << "What is the maximum value of the stat modifier? (used to calculate percentages, multiplied by 5 for most stats; default: 20; values below 1 will result in the default): ";
				getline(cin, tempString);
				tempString.erase(tempString.begin(), remove_if(tempString.begin(), tempString.end(), ::isdigit));
				cout << "tempString = \"" << tempString << "\"\n";
				try {
					paramaters[4] = stoi(tempString);
				} catch (const std::invalid_argument& ia) {
			  	cout << "Invalid argument: Input is not a valid number. Result defaulted to \'20\'\n";
					paramaters[4] = 20;
				}
				paramaters[5] = int(round(paramaters[4] / 2));
				cout << "What is the split point in the possible stat modifier values? (the input number will be the last number in the first group of possible values; the first group will have double the chance to generate. default: half of the stat modifier max value; values in range [-1,1] will result in the default value, values bigger than the stat modifier will result in all numbers having an equal chance to generate, values below zero swaps the groups): ";
				getline(cin, tempString);
				tempString.erase(tempString.begin(), remove_if(tempString.begin(), tempString.end(), isInputSetInt));
				cout << "tempString = \"" << tempString << "\"\n";
				try {
					paramaters[5] = stoi(tempString);
				} catch (const std::invalid_argument& ia) {
			  	cout << "Invalid argument: Input is not a valid number. Result defaulted to \'" << paramaters[5] << "\'\n";
				}
				cout << "What is the maximum amount of downsides you would like? (default: 5; numbers below 1 will result in no maximum, zero will result in no downsides): ";
				getline(cin, tempString);
				tempString.erase(tempString.begin(), remove_if(tempString.begin(), tempString.end(), isInputSetInt));
				cout << "tempString = \"" << tempString << "\"\n";
				try {
					paramaters[6] = stoi(tempString);
				} catch (const std::invalid_argument& ia) {
			  	cout << "Invalid argument: Input is not a valid number. Result defaulted to '10'\n";
					paramaters[6] = 10;
				}
				cout << "\nChoose custom stat data? (y/n): ";
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					cout << "note: the coordinate {0,0} will result in the stat being randomly generated. Also a mod value in range [-1, 1] or a blank input will also have the same result";
					int n = 0;
					int arrNum = 0;
					while (true) {
						if (n >= paramaters[0]) {
							cout << "\nAdding downside...";
						} else {
							cout << "\nAdding upside...";
						}
						cout << "\nChoose the stat coordinates (seperate with comma; e.g. x,y; leave blank or type 'end' to stop adding stats): ";
						getline(cin, tempString);
						if (tempString == "end") {
							break; //from while
						}
						tempString += ",";
						tempString.erase(tempString.begin(), remove_if(tempString.begin(), tempString.end(), isInputSetInt));
						if (count(tempString.begin(), tempString.end(), ',') > 1) {
							tempInt = -1;
							for (int i = 0; i > 2; i++) {
								tempInt = tempString.find_first_of(',');
								statData[n][i] = stoi(string(tempString.begin(), tempString.begin()));
								n++;
							}
							cout << "\nChoose a stat modifier value (a value in range [-1,1] or blank entry will result in a random value): ";
							getline(cin, tempString);
							tempString.erase(tempString.begin(), remove_if(tempString.begin(), tempString.end(), isInputSingleInt));
							if (stoi(tempString) < -1 && stoi(tempString) > 1) {
								statData[arrNum][2] = stoi(tempString);
							} else {
								cout << "Invalid argument: Input is not a valid number. Result defaulted to \'-1\'\n";
								statData[arrNum][2] = -1;
							}
						n++;
						} else {
							cout << "\nError: Not enough values given...\n";
						}
					}
				}
				cout << "\nAre these weapon's stats active? (y/n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[7] = 1;
				} else if (tolower(tempString[0]) == 'n') {
					paramaters[7] = 0;
				} else {
					paramaters[7] = -1;
				}
				cout << "\nDoes this weapon have a meter (Only works if weapon does not already have a meter and if meters are allowed)? (y/n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[8] = 1;
				} else if (tolower(tempString[0]) == 'n') {
					paramaters[7] = 0;
				} else {
					paramaters[7] = -1;
				}
				cout << "\nBypass stat rating? (there will instead be an equal amount of upsides & downsides; y/n; DEFAULT: n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[11] = 1;
				} else {
					paramaters[11] = 0;
				}
				cout << "\nBypass blacklist and dupe stat sheck? (stupidity may ensue; y/n; DEFAULT: n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[12] = 1;
				} else {
					paramaters[12] = 0;
				}
				cout << "\nBypass some specific stats locking the stat modifier value to certian ranges? (stupidity may ensue; y/n; DEFAULT: n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[14] = 1;
				} else {
					paramaters[14] = 0;
				}
				cout << "\nAllow any class to use any weapon? (y/n; DEFAULT: n): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[13] = 1;
				} else {
					paramaters[13] = 0;
				}
				cout << "\nEnable Debug? (y/n; DEFAULT: y): "; 
				getline(cin, tempString);
				if (tolower(tempString[0]) == 'y') {
					paramaters[10] = 1;
				} else {
					paramaters[10] = 0;
				}
			}
		}
		wepGeneration:
		for (int i = 0; i < paramaters.size(); i++) {
			if (i > 8 && paramaters[i] == -1) {
				paramaters[i] = 0;
			}
			cout << "paramaters[" << i << "] = " << paramaters[i] << endl;
		}
		int arr[2] = {paramaters[7], paramaters[8]};
		cout << "Generating weapon... \n";
		weapons.emplace_back(paramaters[0], paramaters[1], paramaters[2], paramaters[3], paramaters[4], paramaters[5], paramaters[6], statData, paramaters[9], paramaters[10], arr, true, paramaters[11], paramaters[12], paramaters[13], paramaters[14]); 
		curWepNum++;
		weapons[curWepNum].printStats(true);
		cout << "press ENTER to continue\n";
		cin.ignore();
	}
}