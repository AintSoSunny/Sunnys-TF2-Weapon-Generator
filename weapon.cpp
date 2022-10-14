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
			for (int j = 0; j <= statCatNum[arr[i][0]]; j++) {
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
			if (realWepSlot == "primary") {
				int arr[3][2] = {
					{1,3},
					{1,13},
					{2,4}
				};	
				addList(arr, sizeof(arr) / sizeof(arr[0])); //this solution is me giving up :)
			} else if (realWepSlot == "secondary") {int arr[1][2] = {{0,0}};} else if (realWepSlot == "melee") {
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
			if (wepType == "Cleaver" || wepType == "Battle Banner") { //most whitelest is shared with cleaver
				int arrWL[5][2] = {
					{0,3},
					{0,11},
					{1,-1},
					{3,1},
					{3,2}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				int arrBL[1][2] = {
					{1,2}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
			}
			if (wepType == "Battle Banner") { //banner exclusive whitelist
				int arrWL[4][2] = {
					{0,11},
					{1,-1},
					{3,1},
					{3,2}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Boots") {
				int arr[1][2] = {
					{5,7}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType == "Flame Thrower") {
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
			} else if (wepType == "Medigun") {
				int arr[4][2] = {
					{5,23},
					{5,24}
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
				int arrBL[2][2] = {
					{0,3},
					{0,9}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[3][2] = {
					{5,0},
					{5,1},
          {5,17}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (tfClass == "Demoman") {
				int arrWL[1][2] = {
					{5,7}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				if (realWepSlot == "melee") {
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
			} else if (tfClass == "Heavy") {
				int arr[2][2] = {
					{5,16},
					{5,17}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (tfClass == "Engineer") {
				int arr[4][2] = {
					{5,18},
					{5,19},
					{5,20},
					{5,21}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
				} else if (tfClass == "Medic") {
					if (wepType == "Medigun") {
						int arrNonMedi[2][2] = {
							{5,23},
							{5,23}
						};
						addList(arrNonMedi, sizeof(arrNonMedi) / sizeof(arrNonMedi[0]), true);
					}
				} else if (tfClass == "Sniper") {
					if (realWepSlot == "primary") {
						int arrPrim[2][2] = {
							{0,1},
							{0,5}
						};
						addList(arrPrim, sizeof(arrPrim) / sizeof(arrPrim[0]));
						int arrPrimWL[5][2] = {
							{5,25},
							{5,26},
							{5,27},
              {5,28},
              {5,29}
						};
						addList(arrPrimWL, sizeof(arrPrimWL) / sizeof(arrPrimWL[0]), true);
				} else if (tfClass == "Spy") {
            int arrPrimWL[6][2] = {
							{5,30},
							{5,31},
							{5,32},
              {5,33},
              {5,34},
              {5,35}
						};
						addList(arrPrimWL, sizeof(arrPrimWL) / sizeof(arrPrimWL[0]), true);
        }
			}
			break;
		case 3:
			//special
			if (whenActive == true) {	
				int arr[1][2] = {
					{1,7}
        };
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (wearable == true) {	
				int arrBL[8][2] = {
					{0,1},
					{0,4},
					{0,6},
					{0,7},
					{1,-1},
					{3,1},
					{3,2},
					{3,7}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[3][2] = {
					{1,7},
					{1,10},
					{1,12}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (hasMeter == true) {
				int arr[1][2] = {
					{5,17}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			}
			if (clipless == true) {
				int arr[5][2] = {
					{0,2},
					{0,8},
					{0,9},
					{1,9},
					{1,15}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} 
			if (rapidFire == true) {
				int arr[3][2] = {
					{0,2},
					{0,5},
					{0,6}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} 
			if (throwable == true) {
				int arrBL[3][2] = {
					{1,-1},
					{2,-1},
					{3,-1}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[3][2] = {
					{3,1},
					{3,2},
					{5,17}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} 
			if (coatable == true) {
				int arrBL[1][2] = { //some already on throwables (all coatables are throwables)
					{1,-1}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[6][2] = {
					{1,0},
					{1,4},
					{1,5},
					{1,9},
					{1,13},
					{1,14}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} 
			if (projectile == true) {
				int arrBL[1][2] = {
					{0,3}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[5][2] = {
					{4,0},
					{4,1},
					{4,2},
					{4,3},
					{4,4}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} 
			if (explosive == true) {
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
Wep::Wep(int num, string pdws, string preDefWepType, int preDefCoords[][2], int preDefProperties[], bool ps, bool debug, bool bypassRating, bool bypassBlacklist) {
	//var assignment
	int preDefWepSlot;
	tempInt = distance(begin(weaponSlots), find(begin(weaponSlots), end(weaponSlots), pdws));
	if (tempInt == distance(begin(weaponSlots), end(weaponSlots))) {
		preDefWepSlot = -1;
	} else {
		preDefWepSlot = -1;
	}
	posNegSplit = false;
	statFlagPass = false;
	tfClass = "Multi";
	ammoType = "bullet";
	statFlag = -1;
	statFlagNum = -1;
	int bannerBuffTypeIndex;
	//statCoords constructer for predefined stats
	tempInt = 0;	
	//second condition only matters when preDefCoords is not defined
	while (preDefCoords[tempInt][0] != -1 && preDefCoords != nullptr) {
		cout << "!!!!\n";
		statCoords.push_back(array<int, 2> ({preDefCoords[tempInt][0], preDefCoords[tempInt][1]})); //copies preDefCoords to statCoords & makes the array not shit (i need to revise most of the arrays b/c most of them are simple lol)
		tempInt++;
		}
	//this seed segment does nothing it just puts the version inside to make sure the seed isn't old
	tempInt = floor(version*100 + subVersion);
	seed.push_back(tempInt);
	fullSeed += to_string(tempInt);
	seedSegLengths.push_back(to_string(tempInt).length());
	//stats Used Chart fill with 0 for the non-exclusive stat groups
	tempInt = sizeof(statCatNum) / sizeof(statCatNum[0]);
 	for (int i = 0; i < tempInt; i++) {
		if (statCatNum[i] != 0) {
			for (int j = 0; j <= statCatNum[i]; j++) {
				if (i < 4) {
					statsUsed[i].push_back(0);	
				} else {
					statsUsed[i].push_back(2);
				}
			}
		}
	}
	//placeholder used by blacklist
	statsUsed[0][0] = 2;
	//slot & weapon choice
	if (preDefWepType == "" || find(begin(weaponList), end(weaponList), preDefWepType) == end(weaponList)) {
		addSeed();
		tempInt = rand() % 100;
		if (preDefWepSlot > -1 && preDefWepSlot < 4) {
			switch(preDefWepSlot){
				case 0:
					tempInt = 0;
					break;
				case 1:
					tempInt = 45;
					break;
				case 2:
					tempInt = 80;
					break;
				default:
					tempInt = 100;
					break;
			}
		}
		if (tempInt < 45) {
			//45% chance
			wepSlot = "primary";
			wepIndexFloor = 0;
			wepIndexCeiling = 15;
		} else if (tempInt >= 45 && tempInt < 80) {
			//35% chance
			wepSlot = "secondary";
			wepIndexFloor = 15;
			wepIndexCeiling = 37;
		} else {
			//20% chance
			wepSlot = "melee";
			wepIndexFloor = 37;
			wepIndexCeiling = 69;
		}
		wepIndexCeiling -= wepIndexFloor;
		wepIndex = rand() % wepIndexCeiling + wepIndexFloor;
		wepType = weaponList[wepIndex];
	} else {
		wepType = preDefWepType;
		wepIndex = distance(begin(weaponList), find(begin(weaponList), end(weaponList), preDefWepType));
		if (wepIndex >= 0 && wepIndex < 15) {
			wepSlot = "primary";
		} else if (wepIndex >= 15 && wepIndex < 37) {
			wepSlot = "secondary";
		} else if (wepIndex >= 37 && wepIndex < 69) {
			wepSlot = "melee";
		} else {
			wepSlot = "PDA1";
		}
	}
	realWepSlot = wepSlot;
	cout << "This weapon is a " << realWepSlot << " weapon!\n";
	blacklist(0);
	cout << "This weapon is a " << wepType << "!\n"; //blacklist comes later
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
  tempInt = rand() % 100;
	//whenActive (decides if stats are passive or active)
  if (wepSlot == "primary" && tempInt < 5 || wepSlot == "secondary" && tempInt < 20 || wepSlot == "melee" && tempInt < 75) {
		whenActive = true;
	} else {
		whenActive = false;
	}
	tempInt = distance(begin(meterWeapons), find(begin(meterWeapons), end(meterWeapons), wepType));
	if (tempInt != distance(begin(meterWeapons), end(meterWeapons))) {
		cout << "This weapon has a " << meterNames[tempInt] << " meter!\n";
		hasMeter = true;
		meterIndex = tempInt;
		meterName = meterNames[tempInt];
		whenActive = false;
	}
	//for weapons that are used more as a primary / secondary 
	if (distance(begin(primaryLike), find(begin(primaryLike), end(primaryLike), wepType)) != distance(begin(primaryLike), end(primaryLike))) {
			cout << "This weapon is like a primary!\n";
			wepSlot = "primary";
		} 
		if (distance(begin(secondaryLike), find(begin(secondaryLike), end(secondaryLike), wepType)) != distance(begin(secondaryLike), end(secondaryLike))) {
			cout << "This weapon is like a secondary!\n";
			wepSlot = "secondary";
		}
	//removes * on "Boots*", "Parachute*", & the shotguns. All weapon checks past this point will not put class into account
	while (wepType.find("*") != string::npos) {
		wepType.erase(wepType.find("*"), 1);
	}
	for (int i = 0; i < 9; i++) {
		/*again, cant use find() in multidimesional array
		this is for weapon ammo types*/
		vector<string> ammoVector(begin(weaponAmmoGroups[i]), end(weaponAmmoGroups[i])); 
		if (find(ammoVector.begin(), ammoVector.end(), wepType) != ammoVector.end()) {
			ammoType = ammoTypes[i];
			break;
		}
	}
  //wearable
	tempInt = distance(begin(wearables), find(begin(wearables), end(wearables), wepType));
	if (tempInt != distance(begin(wearables), end(wearables))) {
		cout << "This weapon is wearable!\n";
		wearable = true;
		whenActive = false;
		wepRating -= wearBoost[tempInt];
		if (tempInt < 2 && realWepSlot == "primary") {
			wepRating -= 25;
		}
		else if (wepType == "Sheild" && num < 4) {
			num = 4;
		}
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
			cout << "This weapon is a projectile weapon!\n";
		} else {
			cout << "This weapon is an explosive weapon!\n";
			explosive = true;
		}
		projectile = true;
	}
	if (distance(begin(cliplessWeapons), find(begin(cliplessWeapons), end(cliplessWeapons), wepType)) != distance(begin(cliplessWeapons), end(cliplessWeapons))) {
		cout << "This weapon has no clip!\n";
		clipless = true;
	}
	if (distance(begin(rapidFireWeapons), find(begin(rapidFireWeapons), end(rapidFireWeapons), wepType)) != distance(begin(rapidFireWeapons), end(rapidFireWeapons))) {
		cout << "This is a rapid fire weapon!\n";
		rapidFire = true;
	}
		tempInt = distance(begin(throwableWeapons), find(begin(throwableWeapons), end(throwableWeapons), wepType));
		if (tempInt != distance(begin(throwableWeapons), end(throwableWeapons))) {
			cout << "This weapon is throwable!\n";
			throwable = true;
			whenActive = false;
			wepRating -= 10;
			if (tempInt < 3) {
				cout << "This weapon is coatable!\n";
				coatable = true;
				wepRating -= 40;
			}
		}	
	blacklist(3);
	//wepType blacklist & class blacklist
	blacklist(1);
	blacklist(2);
	cout << lineBreak("statsUsed[n][n] = n", false, true);
	//statCalculation
	statPhase = 1;
	//n loop is for downsides
	for (int n = 0; n < 2; n++) {
		cout << "statPhase = " << to_string(statPhase);
		for (int i = 0; i < num; i++) {
			if (statPhase == 1) {
				statNum = i;
			} else {
				statNum = num;
			}
			cout << "\n\nstat " << to_string(statNum + 1) << " of " << to_string(num + statPhase - 1) << endl;
			statMade = false;
			/*stat modifier calculation; 
			range is -8 through 20 but negatives are turned positive, so its twice as likely to get 0-8.
			The +2 turns it into 2-10 being most likely to be gotten because no tf2 stat modifes base less than 10%*/
			//makes sure no duplicate stats I think... I hope lol
			//also checks to make sure weapon is balanced during phase 2
			statAttempts = 0;
			while (statMade == false) {
				//determines if stats should be calculated, true means do
				if (statCoords.size() <= statNum) {
					cout << "!\n";
					randomStat = true;		
				}
				if (randomStat == true || tempBool == true) {
					tempBool = false;
					addSeed();
					mod = abs(rand() % 29 - 8);
					if (mod <= 8) {
						mod += 2;
					}
					if (statPhase == 2 && mod > 0 && wepRating > -2.5) {
						mod *= -1;
					}
				statCat = rand() % 6;
				subStat = rand() % (statCatNum[statCat] + 1);
				tempInt = rand() % 100;	
				} else {}
        if (statPhase == 1 && i == 0) {
					cout << "\n!!\n\n";
          if (wepType == "Lunchbox") {
            statCat = 8;
            subStat = 0;
						num = 2;
          } else if (wepType == "Shield" && tfClass == "Demoman") {
						statCat = 8;
            subStat = 1;
					} else if (coatable == true) {
						statCat = 8;
            subStat = 2;
						num = 1;
						if (mod > 10) {
							num++;
						}
					} else if (wepType == "Battle Banner" && mod < 6) {
						if (statCat == 0 or statCat > 3) {
							statCat = rand() % 3 + 1;
						}	
						bannerBuffTypeIndex = statCat;
						statCat = 8;
            subStat = 3;
						num = 2; //at least 1 positive stat 
					} else if (realWepSlot == "primary" && tempInt < 30 || realWepSlot == "secondary" && tempInt < 10 || realWepSlot == "melee" && tempInt < 3) {
							statCat = 8;
							subStat = 4;
					}
        } else if (statPhase == 1 && i < 3) {
					if (wepType == "Battle Banner" && mod > 6) {
						bannerBuffTypeIndex = statCat;
						statCat = 8;
          	subStat = 3;
						num = 3; //at least 1 positive stat
					}
				} else if (statPhase == 2 && statNum == num && statFlag > -1) {
					cout << "Stat flag detected! (SF#" << statFlag << ")\n";
					randomStat = true;
					switch(statFlag) {
						case 0:
							statCat = 2;
							break;
						case 1:
							statCat = 0;
							subStat = 9;
							break;
						case 2:
							statCat = 5;
							subStat = 9;
							statFlagPass = true;
						case 3:
							statCat = 5;
							subStat = 16;
							statFlagPass = true;
							break;
					} //statFlag redirection
				} 
				//statFlagCreation
				cout << "!!!\n";
				tempInt = statFlagNum; //temp storage
				statFlagNum = statNum; //new assignment
				if (statCat == 2 && whenActive == false) { //doesn't need phase check b/c if its phase 2 & this happens there will be no effect;
					statFlag = 0;
					cout << "Stat flag created! (SF#0)\n";
				} else if (statCat == 0 && subStat == 9) {
					statFlag = 1;
					cout << "Stat flag created! (SF#1)\n";
				} else if (statCat == 5 && subStat == 9) {
					statFlag = 2;
					cout << "Stat flag created! (SF#2)\n";
				} else if (statCat == 5 && subStat == 16) {
					statFlag = 3;
					cout << "Stat flag created! (SF#3)\n";
				} else if (statFlagPass == true && statNum > num) {
					statFlagPass = false;
				} else {
					statFlagNum = tempInt; //reverted
				}
				if (statNum != 0 && wepType == "Battle Banner") {
					statCat = bannerBuffTypeIndex;
					cout << "bannerBuffTypeIndex = " << bannerBuffTypeIndex << "; statCat = " << statCat << endl;
					}
				if (statsUsed[statCat][subStat] < statPhase) {
					if (statCat == 8 && randomStat == false) {
						randomStat = true; //so preDef stats can be offset
						num++;
					}
					if (randomStat == true) {
						cout << "!!!!!\n";
						statCoords.push_back(array<int, 2> ({statCat, subStat}));
					}
					posNegSplit = false;
					cout << "Generating stat...";
					wepStats.emplace_back(mod, statCat, subStat, wepType, wepSlot, realWepSlot, tfClass, ammoType, meterName, whenActive, hasMeter, wearable, rapidFire, coatable, explosive, statFlagPass);
					cout << "...stat coordinates = (" << statCat << ", " << subStat << ")\n";
					newWepRating = wepRating + wepStats[statNum].rating;
					if (statPhase == 2 && abs(newWepRating) <= 2.5) {
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nWeapon Complete\n";
						tempString = "wepRating = " + to_string(wepRating);
						cout << tempString << lineBreak(tempString);
						return; //weapon is balanced; end stat creation
					} else if (wepStats.back().statString != "" && statPhase == 1 || wepStats.back().statString != "" && newWepRating >= -2.5) {
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
							statNum++;
							statAttempts = 0;
						}
					} else {
						cout << "Stat creation failed; retrying...\n";
						//undo changes
						seed.pop_back();
						wepStats.pop_back();
						statCoords.pop_back();
						//temp solution / fallback: (usually means bug)
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
					if (statFlagNum == statNum) {	
						cout << "Stat flag removed\n";
						statFlag = -1;
					}
					tempBool = true;
				}
			}
		}
		statPhase = 2;
		//filling half stats with 1s for (int i = 0; i < statCatNum[0]; j++) {}
		replace (statsUsed[0].begin(), statsUsed[0].end(), 0, 1);
	}
	cout << seed.size();
}
void Wep::printStats(bool debug) {
	//for debug :)
	cout << "WEAPON\n\n";
	cout << "Level " << rand() % 100 << " " << wepType << " (" << tfClass << " " << realWepSlot << ")\n\n";
	if (whenActive == true) {
		cout << "When weapon is active:\n";
	}
	for (int i = 0; i < wepStats.size(); i++) {
		cout << wepStats[i].statString << endl;
	}
	if (debug == true) {
		cout << "\nDEBUG INFO\n\nVersion: v." << versionFull << "\nWeapon Rating: " << to_string(wepRating) << "\nstatCoords: ";
		for (int i = 0; i < statCoords.size(); i++) {
			cout << "{" << statCoords[i][0] << ", " << statCoords[i][1] << "}";
			if (i != statCoords.size() - 1) {
				cout << ", ";
			}
		}
		cout << "\nSeed: ";
		if (preSeed == false) {
			for (int i = 0; i < seed.size(); i++) {
				if (i != 0) {
					cout << "-";
				}
				cout << seed[i];
			}
		} else {
			cout << "N/A\n";
		}
		//prolly add more later
	}
	cout << "\n\nEND WEAPON" << lineBreak("END WEAPON");
}