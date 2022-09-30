#include "weapon.hpp"
int Wep::addSeed(int digits) {
	int newSeed = time(NULL) * seedSegLengths.size();
	//idk why I have to use a tempInt compiler is being cringe
	tempInt = pow(10, digits);
	newSeed %= tempInt;
	while (to_string(newSeed).length() < digits) {
		tempInt = newSeed % 10;
		newSeed *= 10;
		newSeed += tempInt;
	}
	newSeed = abs(newSeed);
	srand(newSeed);
	seed.push_back(newSeed);
	seedSegLengths.push_back(digits);
	fullSeed += to_string(newSeed);
	cout << "Added seed: " << newSeed << endl;
	return newSeed;
}
void Wep::addList(int arr[][2], int size, bool whitelist) {
	if (whitelist == true) {
		tempInt = 0; //whitelist doesn't work like an actual whitelist, it just un-blacklists stats instead of exclusively offering some stats. 
	} else {
		tempInt = 2;
	}
	for (int i = 0; i < size; i++) {
		if (arr[i][1] == -1) {
			for (int j = 0; j < statCatNum[arr[i][0]]; j++) {
				statsUsed[arr[i][0]][j] = tempInt;
				cout << "statsUsed[" << arr[i][0] << "][" << j << "] = " << statsUsed[arr[i][0]][j] << endl;	
			}
		} else {
			statsUsed[arr[i][0]][arr[i][1]] = tempInt;
		cout << "statsUsed[" << arr[i][0] << "][" << arr[i][1] << "] = " << statsUsed[arr[i][0]][arr[i][1]] << endl;	
		}
	}
}
void Wep::blacklist(int type) {
	switch(type) { 
		//all arrays with {0,0} are placeholders; case statements are for organization and a phase-like blacklist so nothing is forgotten or repeated
		case 0:
			//slot
			if (wepSlot == "primary") {
				int arr[3][2] = {
					{1,3},
					{1,13},
					{2,4}
				};	
				addList(arr, sizeof(arr) / sizeof(arr[0])); //this solution is me giving up :)
			} else if (wepSlot == "secondary") {int arr[1][2] = {{0,0}};} else if (wepSlot == "melee") {
				int arr[6][2] = {
					{0,1},
					{0,9},
					{1,4},
					{1,6},
					{1,8},
					{1,9}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else {};
			break;
		case 1:
			//weapon
			if (wepType == "Flame Thrower") {
				int arr[2][2] = {
					{5,2},
					{5,3}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType == "Stickybomb Launcher") {
				int arr[6][2] = {
					{5,5},
					{5,6},
					{5,7},
					{5,8},
					{5,9},
					{5,10}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType == "Shield") {
				int arr[5][2] = {
					{5,4},
					{5,11},
					{5,12},
					{5,13},
					{5,14}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType == "Minigun") {
				int arr[2][2] = {
					{5,16},
					{5,17}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType == "Knife") {
				int arr[3][2] = {
					{0,3},
					{0,6},
					{1,13}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else {}
			break;
		case 2:
			//class
			if (tfClass == "Pyro") {
				int arrBL[1][2] = {
					{0,8}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[2][2] = {
					{5,0},
					{5,1}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (tfClass == "Demoman") {
				int arrWL[1][2] = {
					{5,7}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				if (wepSlot == "melee") {
					int arrWLSword[2][2] = {
						{5,14},
						{5,15}
					};
				addList(arrWLSword, sizeof(arrWLSword) / sizeof(arrWLSword[0]), true);
				} else if (wepType == "Boots") {
				int arr[3][2] = {
					{5,4},
					{5,11},
					{5,12}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
				}
			} else if (tfClass == "Sniper") {
				if (wepSlot == "primary") {
					int arrPrim[2][2] = {
						{0,1},
						{0,6}
					};
					addList(arrPrim, sizeof(arrPrim) / sizeof(arrPrim[0]));
				}
			}
			break;
		case 3:
			//special
			if (wearable == true) {	
				int arrBL[5][2] = {
					{0,1},
					{0,9},
					{1,-1},
					{3,1},
					{3,2}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[3][2] = {
					{1,7},
					{1,10},
					{1,12}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (clipless == true) {
				int arr[4][2] = {
					{0,2},
					{0,8},
					{0,9},
					{1,9}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (rapidFire == true) {
				int arr[2][2] = {
					{0,9},
					{0,5}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (projectile == true) {
				int arrWL[5][2] = {
					{4,0},
					{4,1},
					{4,2},
					{4,3},
					{4,4}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (explosive == true) {
				int arrWL[1][2] = {
					{4,-1}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			}
			break;
		default:
			cout << "\nuh oh\n\n";
	}
};
Wep::Wep(int num, bool preSeed){
	//this seed segment does nothing it just puts the version inside to make sure the seed isn't old
	posNegSplit = false;
	tempInt = floor(version*10);
	seed.push_back(tempInt);
	fullSeed += to_string(tempInt);
	seedSegLengths.push_back(to_string(tempInt).length());
	//stats Used Chart fill with 0 for the non-exclusive stat groups
	tempInt = sizeof(statCatNum) / sizeof(statCatNum[0]);
 	for (int i = 0; i < tempInt; i++) {
		if (statCatNum[i] != 0) {
			for (int j = 0; j < statCatNum[i]; j++) {
				if (i < 4) {
					statsUsed[i].push_back(0);	
				} else {
					statsUsed[i].push_back(2);
				}
			}
		}
	}
	//slot & weapon choice
	addSeed();
	tempInt = rand() % 100;
	if (tempInt < 40) {
		//40% chance
		wepSlot = "primary";
		wepIndexFloor = 0;
		wepIndexCeiling = 15;
	} else if (tempInt >= 40 && tempInt <= 65) {
		//35% chance
		wepSlot = "secondary";
		wepIndexFloor = 15;
		wepIndexCeiling = 35;
	} else {
		//25% chance
		wepSlot = "melee";
		wepIndexFloor = 35;
		wepIndexCeiling = 68;
	}
	//placeholder used by blacklist
	statsUsed[0][0] = 2;
	cout << "statsUsed[0][0] = " << statsUsed[0][0] << endl;
	cout << "This weapon is a " << wepSlot << " weapon!\n";
	blacklist(0);
	wepIndexCeiling -= wepIndexFloor;
	wepIndex = rand() % wepIndexCeiling + wepIndexFloor;
	wepType = weaponList[wepIndex];
	cout << "This weapon is a " << wepType << "!\n";
	blacklist(1);
	for (int i = 0; i < 10; i++) {
		/*cant use find() in multidimesional array so... take the array to a vector lol I have no idea if this works :) 
ANYWAYS this determens the class based on the weapon*/
		vector<string> tempVector(begin(classWeapons[i]), end(classWeapons[i])); /* old code:
tempInt = distance(begin(classWeapons), find(begin(classWeapons[classIndex]), end(classWeapons[classIndex]), weaponList[tempInt]));
		if (find(tempVector.begin(), tempVector.end(), weaponList[tempInt]) != tempVector.end()) {
			break;
		}
		*/ 
		if (find(tempVector.begin(), tempVector.end(), wepType) != tempVector.end()) {
			classIndex = i;
			tfClass = classList[i];
			break;
		}
	}
	cout << "This weapon is for the " << tfClass << "!\n";
	blacklist(2);
	//removes * on "Boots*", "Parachute*", & the shotguns
	if (wepType.find("*") != string::npos) {
		wepType.erase(wepType.find("*"), 1);
	}
	//whenActive / wearable
	tempInt = distance(begin(wearables), find(begin(wearables), end(wearables), wepType));
	if (tempInt != distance(begin(wearables), end(wearables))) {
		cout << "This weapon is wearable!\n";
		wearable = true;
		whenActive = false;
		wepRating -= wearBoost[tempInt];
		if (tempInt < 2 && wepSlot == "primary") {
			wepRating -= 25;
		}
		else if (wepType == "Sheild" && num < 4) {
			num = 4;
		}
	} else if (wepSlot == "primary" && tempInt < 5 || wepSlot == "secondary" && tempInt < 20 || wepSlot == "melee" && tempInt < 75) {
		whenActive = true;
	} else {
		whenActive = false;
	}
	//bad, projectile, meter, clipless
	tempInt = distance(begin(alreadyBad), find(begin(alreadyBad), end(alreadyBad), wepType));
	if (tempInt != distance(begin(alreadyBad), end(alreadyBad))) {
		cout << "Bad weapon! (lol)\n";
		wepRating -= howBad[tempInt];
	}
	tempInt = distance(begin(projectileBased), find(begin(projectileBased), end(projectileBased), wepType));
	if (tempInt != distance(begin(projectileBased), end(projectileBased))) {
		if (tempInt < 8) {
			cout << "Projectile weapon!\n";
		} else {
			cout << "Explosive weapon!\n";
			explosive = true;
		}
		projectile = true;
	}
	tempInt = distance(begin(meterWeapons), find(begin(meterWeapons), end(meterWeapons), wepType));
	if (tempInt != distance(begin(meterWeapons), end(meterWeapons))) {
		cout << "This weapon has a " << meterNames[tempInt] << " meter!\n";
		hasMeter = true;
	}
	if (tempInt == distance(begin(cliplessWeapons), find(begin(cliplessWeapons), end(cliplessWeapons), wepType)) != distance(begin(cliplessWeapons), end(cliplessWeapons))) {
		cout << "This weapon has no clip!\n";
	clipless = true;
	}
	if (tempInt == distance(begin(rapidFireWeapons), find(begin(rapidFireWeapons), end(rapidFireWeapons), wepType)) != distance(begin(rapidFireWeapons), end(rapidFireWeapons))) {
		cout << "This is a rapid fire weapon!\n";
	rapidFire = true;
	}
	blacklist(3);
	statPhase = 1;
	//n loop is for downsides
	for (int n = 0; n < 2; n++) {
		cout << "statPhase = " << to_string(statPhase);
		for (int i = 0; i < num; i++) {
			if (statPhase == 1) {
				statNum = i;
			} else {
				statNum = num + 1;
			}
			cout << "\n\nstat " << to_string(i + 1) << " of " << to_string(num) << endl;
			statMade = false;
			/*stat modifier calculation; 
			range is -8 through 20 but negatives are turned positive, so its twice as likely to get 0-8.
			The +2 turns it into 2-10 being most likely to be gotten because no tf2 stat modifes base less than 10%*/
			//makes sure no duplicate stats I think... I hope lol
			//also checks to make sure weapon is balanced during phase 2
			statAttempts = 0;
			while (statMade == false) {
				addSeed();
				mod = abs(rand() % 29 - 8);
				if (mod <= 8) {
					mod += 2;
				}
				if (statPhase == 2 && mod > 0 && wepRating >= -2.5) {
					mod *= -1;
				}
				statCat = rand() % 6;
				subStat = rand() % statCatNum[statCat];
				if (statPhase == 1) {
					tempInt = 1;
				} else {
					tempInt = 2;
				}
				if (statsUsed[statCat][subStat] < tempInt && wepStats.back().statString != "") {
					posNegSplit = false;
					cout << "Generating stat...";
					wepStats.emplace_back(mod, statCat, subStat, wepType, wepSlot, tfClass, whenActive, hasMeter, wearable, rapidFire);
					newWepRating = wepRating + wepStats[statNum].rating;
					cout << "...stat coordinates = (" << statCat << ", " << subStat << ")\n";
					if (statPhase == 2 && 0.1 * (abs(newWepRating) + 1) <= 0.35) {
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nWeapon Complete\n";
						cout << "wepRating = " << wepRating;
						return; //weapon is balanced; end stat creation
					} else if (statPhase == 1 or newWepRating >= -5) {
						cout << "Stat creation successful!\n";
						if (posNegSplit == true) {
							statsUsed[statCat][subStat] += 1;
						} else {
							statsUsed[statCat][subStat] += 2;	
						}
						cout << "statsUsed[" << statCat << "][" << subStat << "] = " << statsUsed[statCat][subStat] << endl;
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nstat coordinates = (" << statCat << ", " << subStat << ")\n";
						cout << "\nwepRating = " << wepRating << endl;
						//except for some reason this if else works ???
						if (statPhase == 1) {
							statMade = true; //breaks while loop for first phase
						} else {
							statNum += 1;
							statAttempts = 0;
						}
					} else {
						cout << "Stat creation failed; retrying...\n";
						//undo changes
						seed.pop_back();
						wepStats.pop_back();
						//temp solution / fallback:
						statAttempts++;
						if (statAttempts > 50) {
								cout << "Stat creation aborted...Weapon Complete\n";
							cout << "wepRating = " << wepRating;
								return;
						}
					}
				} else {
					cout << "Stat taken! Seed removed\n";
					seed.pop_back();
				}
			}
		}
		statPhase = 2;
		num = 1;
		//filling half stats with 1s for (int i = 0; i < statCatNum[0]; j++) {}
		replace (statsUsed[0].begin(), statsUsed[0].end(), 0, 1);
	}
	cout << seed.size();
}
void Wep::printStats(bool debug) {
	//for debug :)
	cout << "\nWEAPON\n\n";
	cout << "Level " << rand() % 100 << " " << wepType << " (" << tfClass << " " << wepSlot << ")\n\n";
	if (whenActive == true) {
		cout << "When weapon is active:\n";
	}
	for (int i = 0; i < wepStats.size(); i++) {
		cout << wepStats[i].statString << endl;
	}
	if (debug == true) {
		cout << "\n\nDEBUG INFO\n\nWeapon Rating: " << to_string(wepRating) << endl;
		cout << "Seed: ";
		for (int i = 0; i < seed.size(); i++) {
			if (i != 0) {
				cout << "-";
			}
			cout << seed[i];
		}
		//prolly add more later
	}
	cout << "\n\nEND WEAPON\n\n";
}