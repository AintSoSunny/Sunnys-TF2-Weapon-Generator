#include "weapon.hpp"
const array<array<int,2>,20> statsToOutside = {{
	//all (0-10)
	{1,3},
	{1,11},
	{1,13},
	{1,14},
	{1,15},
	{4,1},
	{4,2},
	{4,7},
	{5,0},
	{5,17},
	{5,26},
	//banner (10-14)
	{1,7},
	{2,1},
	{2,2},
	{3,1},
	{3,2}
}};
const array<array<int,2>,25> posNegSplitStats = {{ //besides statCat 0
	{1,3},
	{1,13},
	{1,14},
	{1,16},
	{2,1},
	{4,1},
	{4,2},
	{4,9},
	{5,0},
	{5,12},
	{5,15},
	{5,17},
	{5,18},
	{5,26},
	{5,27},
	{5,28},
	{5,29},
	{5,34},
	{5,35},
	{5,36},
	{5,37},
	{5,40},
	{5,43},
	{8,7},
}};
int Wep::addSeed(int digits) {
	if (digits < 1) {
		digits = 3;
	}
	int newSeed = time(NULL) * seedSegLengths.size();
	//idk why I have to use a tempInt compiler is being cringe
	tempInt = pow(10, digits);
	newSeed %= tempInt;
	newSeed = abs(newSeed);
	while (to_string(newSeed).length() < digits) {
		newSeed = abs(newSeed);
		//cout << "(pre-mod) tempInt = " << tempInt << "; newSeed = " << newSeed << endl;
		tempInt = newSeed % 10;
		if (newSeed == 0 && digits != 1) {
			newSeed++; //prevents an infinite loop of seed forever being zero which is one digit
		}
		newSeed *= 10;
		newSeed += tempInt;
		/*cout << "(post-mod) tempInt = " << tempInt << "; newSeed = " << newSeed << "\nPress ENTER to continue\n";
		cin.ignore();*/
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
	cout << endl;
	if (whitelist) {
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
			if (wepSlot == "primary") {
				int arr[2][2] = {
					{0,5},
					{2,4}
				};	
				addList(arr, sizeof(arr) / sizeof(arr[0])); //this solution is me giving up :)
			} else if (wepSlot == "secondary") {
				int arr[1][2] = {
					{1,15}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} 
			if (realWepSlot == "melee") {
				int arr[5][2] = {
					{0,1},
					{0,9},
					{1,4},
					{1,6},
					{1,9}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else {};
			break;
		case 1:
			//weapon
			if (wepType == "Cleaver") { //most whitelest is shared with cleaver
				int arrWL[10][2] = {
					{0,3},
					{0,11},
					{1,0},
					{1,1},
					{1,2},
					{1,3},
					{1,11},
					{1,13},
					{1,14},
					{5,40}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				/*int arrBL[1][2] = {
					{1,2}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));*/
			}
			if (wepType == "Lunchbox") { //lunchbox no longer 'throwable' due to having effects after consumption (like banner but only for you) (may change)
				int arrBL[6][2] = {
					{0,-1},
					{1,-1},
					{3,1},
					{3,2},
					{3,3},
					{5,17},
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[8][2] = {
					{0,3},
					{0,10},
					{1,13},
					{1,14},
					{5,13},
					{5,26},
					{8,0}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			}
			if (wepType == "Battle Banner") {
				noDownsides = true;
				int arrWL[8][2] = {
					{0,11},
					{1,-1},
					{3,1},
					{3,2},
					{4,4},
					{5,17},
					{8,1},
					{8,3}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				int arrBL[4][2] = {
					{1,2},
					{1,6},
					{1,8},
					{2,1}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
			} else if (wepType == "Boots") {
				int arr[1][2] = {
					{5,7}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType.substr(0,5) == "Flame") {
				int arrBL[1][2] = {
					{4,1}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[2][2] = {
					{5,2},
					{5,3}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Flare Gun") {
				int arrWL[2][2] = {
					{1,8},
					{1,15}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Grenade Launcher") {
				int arr[1][2] = {
					{4,1}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
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
			} else if (wepType == "Minigun") {
				int arrBL[1][2] = {
					{1,15}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[2][2] = {
					{5,16},
					{5,17}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Wrench") {
				int arr[6][2] = {
					{1,8},
					{5,19},
					{5,20},
					{5,21},
					{5,38},
					{5,39}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (wepType == "Syringe Gun") {
				int arrBL[1][2] = {
					{4,2}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[1][2] = {
					{5,22}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Medigun") {
				int arrBL[4][2] = {
					{0,-1},
					{1,-1},
					{3,6},
					{3,9}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[9][2] = {
					{0,3},
					{1,0},
					{1,1},
					{1,8},
					{5,23},
					{8,6},
					{5,41},
					{5,42},
					{5,43}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Bonesaw") {
				int arr[1][2] = {
					{5,24}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (wepType == "Sapper") {
				whenActive = true;
				int arrBL[4][2] = {
					{0,-1},
					{1,-1},
					{3,5},
					{3,6}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[2][2] = {
					{1,0},
					{1,14}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Knife") {
				int arrBL[8][2] = {
					{0,2},
					{0,3},
					{0,4},
					{0,6},
					{1,-1},
					{1,11},
					{1,13}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[4][2] = {
					{1,5},
					{1,7},
					{1,12},
					{1,14}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Invis Watch") {
				int arrBL[8][2] = {
					{0,2},
					{1,7},
					{2,3},
					{3,3},
					{3,6},
					{3,7},
					{3,9},
					{5,17}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[7][2] = {
					{5,30},
					{5,31},
					{5,32},
					{5,33},
					{5,34},
					{5,35},
					{8,7}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else {}
			break;
		case 2:
			//class
			if (tfClass == "Scout") {
				int arr[1][2] = {
					{0,5}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			}	if (tfClass == "Pyro") {
				int arrBL[3][2] = {
					{0,3},
					{0,9},
					{4,6}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[4][2] = {
					{5,0},
					{5,1},
          {5,17}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				if (wepSlot == "melee") {
					int arr[1][2] = {
						{1,8}
					};
					addList(arr, sizeof(arr) / sizeof(arr[0]), true);
				}
			} else if (tfClass == "Demoman") {
				int arr[1][2] = {
					{1,8}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
				if (explosive) {
					int arrWL[1][2] = {
						{5,7}
					};
					addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
				} else if (wepType == "Boots") {
					int arr[3][2] = {
						{5,4},
						{5,11},
						{5,12}
					};
					addList(arr, sizeof(arr) / sizeof(arr[0]), true);
				} else if (wepType == "Shield") {
					int arr[7][2] = {
						{1,8},
						{5,4},
						{5,11},
						{5,12},
						{5,13},
						{5,14},
						{8,1}
					};
					addList(arr, sizeof(arr) / sizeof(arr[0]), true);
				} else if (wepType == "Sword") {
					int arrWLSword[3][2] = {
						{1,8},	
						{5,14},
						{5,15}
					};
				addList(arrWLSword, sizeof(arrWLSword) / sizeof(arrWLSword[0]), true);
				}
			} else if (tfClass == "Heavy") {
				int arr[1][2] = {
					{5,17}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (tfClass == "Engineer") {
				int arr[2][2] = {
					{5,18},
					{5,33}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			} else if (tfClass == "Medic") {
				int arr[2][2] = {
					{0,5},
					{1,8}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (tfClass == "Sniper") {
				if (realWepSlot == "primary") {
					int arrPrim[4][2] = {
						{0,1},
						{0,3},
						{0,6},
						{1,15}
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
				}
				int arrWL[5][2] = {
					{1,8}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (tfClass == "Spy") {
        int arrBL[1][2] = {
					{0,10}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), true);
				int arrWL[7][2] = {
					{1,8},
					{5,30},
					{5,31},
					{5,32},
        	{5,33},
         	{5,34},
        	{5,35}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
      }
			break;
		case 3:
			//special
			if (whenActive && wepType != "Battle Banner" && wepType != "Lunchbox" && !(wepSlot == "melee" || wearable)) {	
				int arr[1][2] = {
					{1,7}
        };
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (wearable) {	
				int arrBL[9][2] = {
					{0,1},
					{0,4},
					{0,5},
					{0,6},
					{0,7},
					{1,-1},
					{3,1},
					{3,2},
					{3,7}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[4][2] = {
					{1,7},
					{1,10},
					{1,12},
					{5,17}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (hasMeter) {
				int arr[1][2] = {
					{5,13}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]), true);
			}
			if (clipless) {
				int arr[6][2] = {
					{0,2},
					{0,6},
					{0,8},
					{0,9},
					{1,9},
					{1,16}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} 
			if (rapidFire) {
				int arr[5][2] = {
					{0,1},
					{0,2},
					{0,6},
					{1,16}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} 
			if (throwable) {
				int arrBL[4][2] = {
					{0,-1},
					{1,-1},
					{2,-1},
					{3,-1}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[6][2] = {
					{0,3},
					{0,6},
					{0,10},
					{0,11},
					{3,1},
					{3,2}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} 
			if (coatable) {
				/*int arrBL[1][2] = { //some already on throwables (all coatables are throwables)
					{8,3}
				}
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));*/
				int arrWL[7][2] = {
					{1,0},
					{1,13},
					{1,14},
					{4,4},
					{5,20},
					{5,26},
					{8,2}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} 
			if (explosive) {
				int arrWL[1][2] = {
					{4,-1}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			}
			if (projectile) {
				int arrBL[3][2] = {
					{1,4},
					{1,8}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]), false);
				int arrWL[3][2] = {
					{4,0},
					{4,1},
					{4,2}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} 
			if (critGimmick) {
				int arr[3][2] = {
					{1,0},
					{1,1},
					{1,2}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			}
			break;
		case 4: //downside blacklist
			cout << "Downside blacklist: ";
			if (wepType == "Lunchbox") {
				int arr[1][2] = {
					{1,-1}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (wepType == "Shield" && tfClass == "Demoman") {
				int arr[2][2] = {
					{2,0},
					{2,1}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (coatable) {
				int arr[3][2] = {
					{0,-1},
					{1,-1},
					{5,20}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (wepType == "Sniper Rifle") {
				int arrBL[2][2] = {
					{1,2},
					{1,11}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
			} else if (critGimmick) {
				int arrBL[2][2] = {
					{1,2},
					{1,11}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[1][2] = {
					{1,1}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (wepType == "Medigun") {
				int arrBL[3][2] = {
					{1,-1},
					{2,-1},
					{3,-1}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[1][2] = {
					{2,3}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else {
				cout << "N/A";
			}
			cout << endl;
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
	noDownsides = false;
	statFlagPass = false;
	bannerBuffTypeIndex = -1;
	invisWatchCloakTypeIndex = -1;
	invisWatchFeignDuration = -1;
	tfClass = "Multi";
	ammoType = "bullet";
	statFlag = -1;
	tempInt = 0;
	array<int,1> upsideStatFlags = {5};
	/*statCoords constructer for predefined stats
	second condition only matters when preDefCoords is not defined*/
	while (preDefCoords[tempInt][0] != -1 && preDefCoords != nullptr) {
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
					//cout << "statsUsed[" << i << "][" << j << "] = " << statsUsed[i][j] << endl;
				}
			}
		}
	}
	//placeholder used by blacklist
	statsUsed[0][0] = 2;
	/*seasonal silly stat
	statsUsed[5][44] = 0;*/
	//slot & weapon choice
	if (preDefWepType == "" || find(begin(weaponList), end(weaponList), preDefWepType) == end(weaponList)) {
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
					tempInt = 99;
					break;
			}
		} else {
			addSeed();
			tempInt = rand() % 100;
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
		} else if (tempInt >= 80 && tempInt < 99) {
			//19% chance
			wepSlot = "melee";
			wepIndexFloor = 37;
			wepIndexCeiling = 68;
		} else {
			wepSlot = "PDA1";
			wepType = "Invis Watch";
		}
		if (wepSlot != "PDA1") {
			wepIndexCeiling -= wepIndexFloor;
			wepIndex = rand() % wepIndexCeiling + wepIndexFloor;
			wepType = weaponList[wepIndex];	
		}
	} else {
		wepType = preDefWepType;
		wepIndex = distance(begin(weaponList), find(begin(weaponList), end(weaponList), preDefWepType));
		if (wepIndex >= 0 && wepIndex < 15) {
			wepSlot = "primary";
		} else if (wepIndex >= 15 && wepIndex < 37) {
			wepSlot = "secondary";
		} else if (wepIndex >= 37 && wepIndex < 68) {
			wepSlot = "melee";
		} else {
			wepSlot = "PDA1";
		}
	}
	realWepSlot = wepSlot;
	cout << "This weapon is a " << realWepSlot << " weapon!\n";
	cout << "This weapon is a " << wepType << "!\n";
	for (int i = 0; i < 10; i++) {
		/*cant use find() in multidimesional array so... take the array to a vector lol I have no idea if this works :) 
ANYWAYS this determens the class based on the weapon*/
		vector<string> tempVector(classWeapons[i].begin(), classWeapons[i].end()); /* old code:
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
	
	//for weapons that are used more as a primary / secondary 
	if (distance(begin(primaryLike), find(begin(primaryLike), end(primaryLike), wepType)) != distance(begin(primaryLike), end(primaryLike))) {
			cout << "This weapon is like a primary!\n";
			wepSlot = "primary";
		} 
		if (distance(begin(secondaryLike), find(begin(secondaryLike), end(secondaryLike), wepType)) != distance(begin(secondaryLike), end(secondaryLike))) {
			cout << "This weapon is like a secondary!\n";
			wepSlot = "secondary";
		}
  tempInt = rand() % 100;
	cout << "tempInt = " << tempInt << endl;
	//whenActive (decides if stats are passive or active)
  if ((wepSlot == "primary" && tempInt < 15) || (wepSlot == "secondary" && tempInt < 50) || (wepSlot == "melee" && tempInt < 85)) {
		whenActive = true;
	} else {
		whenActive = false;
	}
	tempInt = distance(begin(meterWeapons), find(begin(meterWeapons), end(meterWeapons), wepType));
	if (tempInt != distance(begin(meterWeapons), end(meterWeapons))) {
		hasMeter = true;
		meterIndex = tempInt;
		meterName = meterNames[tempInt];
	}
	//clipless (if weapons dont have a clip, e.g. Minigun, Flare Gun, Sniper Rifle)
	if (distance(begin(cliplessWeapons), find(begin(cliplessWeapons), end(cliplessWeapons), wepType)) != distance(begin(cliplessWeapons), end(cliplessWeapons))) {
		cout << "This weapon has no clip!\n";
		clipless = true;
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
		} else if (miscAmmo) {
			ammoType = "$M";
		} else if (realWepSlot != "melee" && !wearable) {
			ammoType = "bullet";
		} else {
			ammoType = "\nIF YOU ARE SEEING THIS TEXT, SOMETHING WENT WRONG\nISSUE: Stat that uses ammo has been assigned to a melee weapon without misc ammo / a wearable weapon type\n\n{CONTINUE}\n";
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
			wepRating += 10;
		} else if (wepType == "Shield" && tfClass == "Sniper") {
			wepRating += 25;
		}
	}
	//bad, projectile, meter
	tempInt = distance(begin(alreadyBad), find(begin(alreadyBad), end(alreadyBad), wepType));
	if (tempInt != distance(begin(alreadyBad), end(alreadyBad))) {
		cout << "Bad weapon! (lol)\n";
		wepRating -= howBad[tempInt];
	}
	tempInt = distance(begin(projectileBased), find(begin(projectileBased), end(projectileBased), wepType));
	if (tempInt != distance(begin(projectileBased), end(projectileBased))) {
		if (tempInt < 5) {
			cout << "This weapon is a projectile weapon!\n";
		} else {
			cout << "This weapon is an explosive weapon!\n";
			explosive = true;
		}
		projectile = true;
		if (ammoType == "bullet") {
			ammoType = "projectile";
		}
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
			wepRating -= 15;
			if (tempInt < 3) {
				cout << "This weapon is coatable!\n";
				coatable = true;
				projectile = true;
				ammoType = "Jar";
				if (wepType == "Gas Canister") {
					ammoType = wepType;
				}
				wepRating -= 30;
			}
		}	
	blacklist(0);
	blacklist(3);
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
			The +2 turns it into 2-10 being most likely to be gotten because no tf2 stat modifes base less than 10%
			makes sure no duplicate stats I think... I hope lol
			also checks to make sure weapon is balanced during phase 2*/
			statAttempts = 0;
			while (!statMade) {
				cout << endl;
				//determines if stats should be calculated, true means do
				if (statCoords.size() <= statNum) {
					randomStat = true;		
				}
				if (randomStat || tempBool) {
					tempBool = false;
					addSeed();
					mod = abs(rand() % 29 - 8);
					if (mod <= 8) {
						mod += 2;
					}
					if (forceDownside || statPhase == 2 && mod > 0 && wepRating > -2.5 && !forceUpside) {
						mod *= -1;
						if (!downsideBlacklistApplied) {
							downsideBlacklistApplied = true;
							blacklist(4);
						}
					}
					if (forceDur >= 0) {
						forceDur--;
						if (forceDur <= 0) {
							forceDur = -1;
							forceUpside = false;
							forceDownside = false;
						}
					}
					statCat = rand() % 6;	
					if (coatable && mod < 0) {
						if (statCat % 2 == 0) {
							statCat = 5;
						} else {
							statCat = 4;
						}
					} else if (meterStatBoostNum > 0 && statCat == 2) {
						statCat = 1;
					}
					subStat = rand() % (statCatNum[statCat] + 1);
					tempInt = rand() % 100;	
				} else {}
				//here is temp
				//cout << "statCat = " << statCat << "; subStat = " << subStat << "; mod = " << mod << "; statFlags.back() = " << statFlags.back() << endl;
				if (statFlags.back() > -1) {
					//cout << "\n\nOhSheeetARat\n\n\n";
					statFlagPass = false;
					statFlag = statFlags.back();
					//this is temporary 
					for (int i = 0; i < statFlags.size(); i++) {
						cout << "statFlags[" << i << "] = " << statFlags[i] << endl;
					}
					cout << "statFlag = " << statFlag << endl;
					if (mod < 0 && statFlags.back() != 5 && statFlags.back() != 10) {
						cout << "Stat flag detected! (SF#" << statFlag << ")\n";
						randomStat = true; //so statcoords are added regardless
						statFlags.pop_back();
						switch(statFlag) {
							case 1:
								statCat = 0;
								subStat = 9;
								break;
							case 2:
								statCat = 4;
								subStat = 9;
								statFlagPass = true;
							case 3:
								statCat = 5;
								subStat = 16;
								statFlagPass = true;
								break;
							case 4: //tickle mittens pt.2
								statCat = 0;
								subStat = 7;
								statFlagPass = true;
								miscAmmo = false;
								break;
							case 6:
								statCat = 5;
								subStat = 17;
								break;
							case 7:
								statCat = 4;
								subStat = 7;
								break;
							case 8:
								statCat = 1;
								subStat = 16;
								break;
							case 9:
								statCat = 8;
								subStat = 7;
								statFlagPass = true;
								break;
							case 11:
								statCat = 2;
								subStat = statCatNum[2] + 1;
								break;
							case 12:
								statCat = 1;
								subStat = 11;
								break;
							case 13:
								statCat = 5;
								subStat = 0;
								break;
						} //statFlag redirection	
					} else if (mod > 0 && statFlag % 5 == 0) {
						cout << "Stat flag detected! (SF#" << statFlag << ")\n";
						randomStat = true; //so statcoords are added regardless
						statFlags.pop_back();
						switch(statFlag) {
							case 0:
								statCat = 1;
								subStat = 6;
								break;
							case 5:
							miscAmmo = true;
							if (mod < 4) {
								statCat = 0;
								subStat = 6;
							} else if (mod >= 4 && mod < 9) {
								statCat = 1;
								subStat = 3;
							} else {
								statCat = 1;
								subStat = 11;
							}
							break;
						case 10:
							statCat = 5;
							subStat = 20;
							break;
						case 15:
							statCat = 1;
							subStat = 8;
							break;
						}
					} else if (mod < 0 && statFlag % 5 == 0) {
						statFlags.pop_back();
						statFlag = -1;
					}
				} 
				//special weapon constructor redirection / other stat stuff
				if (statNum == 0) {
          if (wepType == "Lunchbox") {
						if (statAttempts == 0) {
							wepRating -= 100;
						}
            statCat = 8;
            subStat = 0;
						num = 1;
          } else if (wepType == "Shield" && tfClass == "Demoman") {
						statCat = 8;
            subStat = 1;
						num = 1;
					} else if (coatable) {
						statCat = 8;
            subStat = 2;
						num = 1;
						if (mod > 10) {
							num++;
						}
					} else if (wepType == "Battle Banner" && (mod < 8 || statCat != 2 && statCat != 3)) {
						noDownsides = true;
						statCat = rand() % 3 + 1;
						if (bannerBuffTypeIndex <= 0) {
							bannerBuffTypeIndex = statCat;
						}
						statCat = 8;
            subStat = 3;
						num = 2; //at least 1 positive stat 
					} else if (!(wearable || throwable || wepType == "Medigun") && (realWepSlot == "primary" && tempInt < 6) || (realWepSlot == "secondary" && tempInt < 4) || (wepSlot == "melee" && tempInt < 2)) {
						/*if (tempInt % 2 != 0) {*/
							cout << "!METER!";
							hasMeter = true;
							meterName = classMeterNames[classIndex][rand() % classMeterNames[classIndex].size()];
							statCat = 8;
							subStat = 4;
							int arr[2][2] = {
								{5,13},
								{8,4}
							};
							addList(arr, sizeof(arr) / sizeof(arr[0]), true);
							if (wepType != "melee") {
								if (whenActive) {
									whenActive = false;
								} else {
									whenActive = true;
								}
							}
						/*} else {
							cout << "!COUNTER!";
							hasCounter = true;
							statCat = 8;
							subStat = 5;
						}*/
						num = 1;
					} else if (wepType == "Medigun") {
						whenActive = false;
						if (statAttempts == 0) {
							wepRating -= 50;
						} //stock uber rating
						statCat = 8;
						subStat = 6;
					} else if (wepType == "Invis Watch") {
						num = 1;
						statCat = 8;
						subStat = 7;
					} else if (wepType == "Sword" && tfClass == "Demoman") {
						statCat = 0;
						subStat = 11;
					}
        } else if (statNum < 3) {
					if (wepType == "Battle Banner" && statsUsed[8][3] == 0 && (statPhase == 2 || (statCat != 2 && statCat != 3))) {
						statCat = rand() % 3 + 1;
						if (bannerBuffTypeIndex <= 0) {
							bannerBuffTypeIndex = statCat;
						}
						noDownsides = true;
						statCat = 8;
          	subStat = 3;
						num = 3; //at least 1 positive stat
					} else if (wepType == "Lunchbox" && lunchboxDuration == 0) { //this is all some sort of fail-safe stuff idek
						tempInt = rand() % 10 + statAttempts;
						cout << "tempInt = " << tempInt << endl;
						if (tempInt < 12) {
							statCat = 5;		
		        	subStat = 13;
						} else if (tempInt > 24) {
							statCat = 1;		
		        	subStat = 5;
						} else {
							tempInt = -1;
						}
						if (tempInt > 0) {
							mod = wepRating / (0.4 * (rand() % 10)); //idk
						}
						//this is actually meaningful its a late blacklist so stats that pertain to lunchbox effects can generate
						int arr[2][2] = {
							{2,-1},
							{3,-1}
						};
						addList(arr, 2);
					}
				} 
				if (statNum != 0 && wepType == "Battle Banner" && bannerBuffTypeIndex > 0) {
					if (!(bannerBuffTypeIndex == 3 && statCat >= 3) && statAttempts < 65) {
						statCat = bannerBuffTypeIndex;
						subStat %= statCatNum[statCat] + 1;
					}
				}
				if (mod > 0) {
					tempInt = 1;
				} else {
					tempInt = 2;
				}
				if (statsUsed[statCat][subStat] < tempInt) {
					if (statCat == 8 && !randomStat) {
						randomStat = true; //so preDef stats can be offset
						num++;
					}
					posNegSplit = false;
					cout << "Generating stat.../{";
					wepStats.emplace_back(mod, statCat, subStat, wepType, wepSlot, realWepSlot, tfClass, ammoType, meterName, whenActive, hasMeter, hasAltFire, wearable, rapidFire, coatable, explosive, clipless, critGimmick, miscAmmo, statFlagPass);
					cout << "}\\...\n";
					if (randomStat) {
						statCoords.insert(statCoords.begin() + statNum, wepStats.back().coords);
					}
					newWepRating = wepRating + wepStats.back().rating;
					for (int i = 0; i < posNegSplitStats.size(); i++) {
						if (statCoords[statNum] == posNegSplitStats[i] || statCat == 0) {
							posNegSplit = true;
							break;
						}
					}
					//cout << "posNegSplit = " << posNegSplit << endl;
					if (statPhase == 2 && abs(newWepRating) <= 2.5 && wepStats.back().statString != "") {
						cout << "Stat creation successful!\n";
						//cout << "\nwepStats.size() = " << wepStats.size() << "; statNum = " << statNum << endl;
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nwepRating = " << to_string(wepRating) << endl;
						//stats to outside
						for (int i = 0; i < statNum + 1; i++) {
							//cout << "\ni = " << i << endl;
							for (int j = 0; j < statsToOutside.size(); j++) {
								if (wepType == "Battle Banner" && j < 10) {
									j = 10;
								}
								if (j == 10) {
									/*if (wepType == "Flare Gun") {
										j = 14; 
									} else */if (wepType != "Battle Banner") {
										break;
									}
								}
								//cout << "j = " << j << "\nDoes {" << wepStats[i].coords[0] << "," << wepStats[i].coords[1] << "} = {" << statsToOutside[j][0] << "," << statsToOutside[j][1] << "} or {0,n}? ";
								if (wepStats[i].coords[0] == 0 || wepStats[i].coords == statsToOutside[j]) {
									//cout << "Yes, moving stat to outisde of weapon stats\n";
									if (wepStats[i].realUpside) {
										if (coatable || (hasMeter && wepStats.front().statString.find("Build") != string::npos) || (wepType == "Sword" && tfClass == "Demoman")) {
											tempInt = 1;
										} else {
											tempInt = 0;
										}
										if (wepType == "Battle Banner" && (statCat == 0 || (statCat == 1 && (subStat == 13 || subStat == 14)))) {
											cout << "!!!!!!!!!\n";
											for (int i = 0; i < wepStats.size(); i++) {
												if (wepStats[i].statString.find("Provides") != string::npos) {
													tempInt = i;
													break;
												} else {tempInt = 0;}
											}
											}
										rotate(wepStats.begin() + tempInt, wepStats.begin() + i, wepStats.begin() + i + 1);
										rotate(statCoords.begin() + tempInt, statCoords.begin() + i, statCoords.begin() + i + 1);
										tempInt = 0;
									} else {
										swap(wepStats[i], wepStats[statNum]);
										swap(statCoords[i], statCoords[statNum]);
										i--;
										statNum--; //we can make statNum inaccurate for now it will be reset after
									}
									break;
								} else {
									//cout << "No.\n";
								}
							}
						}
						statNum = wepStats.size() - 1;
						cout << "\nWeapon Complete\n" << lineBreak("Weapon Complete") << endl;
						return; //weapon is balanced; end stat creation
					} else if (wepStats.back().statString != "" && abs(newWepRating) < 1000 &&
					((!noDownsides && 
					(statPhase == 1 || newWepRating >= -2.5 || wepRating < -2.5))
					//banner conditions
					|| (noDownsides && newWepRating < 2.5))) {
						if (posNegSplit) {
							statsUsed[statCat][subStat] += 1;
						} else {
							statsUsed[statCat][subStat] += 2;	
						}
						cout << "Stat creation successful!\n";
						//cout << "statsUsed[" << statCat << "][" << subStat << "] = " << statsUsed[statCat][subStat] << endl;
						//cout << "wepStats.size() = " << wepStats.size() << "; statNum = " << statNum << endl;
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nwepRating = " << wepRating << endl;
						//stat flag creation & other stat specific stuff 
						if (mod > 0) {
							upsideNum++;
							if (statCoords.back() == array<int,2>({0,9}) && wepSlot == "melee") {
								statFlags.push_back(1);
								cout << "Stat flag created! (SF#1)\n";
							} 
							if (statCoords.back() == array<int,2>({4,9})) {
								statFlags.push_back(2);
								cout << "Stat flag created! (SF#2)\n";
							} 
							if (statCoords.back() == array<int,2>({5,16})) {
								statFlags.push_back(3);
								cout << "Stat flag created! (SF#3)\n";
							} 
							if (statCoords.back() == array<int,2>({0,7})) {
								statFlags.push_back(4);
								cout << "Stat flag created! (SF#4)\n";
								statFlags.push_back(5);
								cout << "Stat flag created! (SF#5)\n";
								cout << "statNum = " << statNum << endl;
								if (statNum == num) {
									num++;
								}
							} 
							if (statCoords.back() == array<int,2>({5,17}) && (wepType == "Minigun" || wepType == "Flare Gun")) {
								statFlags.push_back(6);
								cout << "Stat flag created! (SF#6)\n";
							}
							if (statCoords.back() == array<int,2>({4,7}) && statFlags.back() != 7) {
								statFlags.push_back(7);
								cout << "Stat flag created! (SF#7)\n";
							} 
							if (statCoords.back() == array<int,2>({1,16})) {
									statFlags.push_back(0);
									cout << "Stat flag created! (SF#0)\n";
								if (explosive) {
									statFlags.push_back(8);
									cout << "Stat flag created! (SF#8)\n";
								}
							}
							if (invisWatchCloakTypeIndex == 2 && statNum == 1 && statFlags.back() != 9) {
								statFlags.push_back(9);
								cout << "Stat flag created! (SF#9)\n";
								int arrFeignDeath[5][2] = {
									{2,0},
									{2,4},
									{5,30},
									{5,33},
									{5,34}
								};
								addList(arrFeignDeath, sizeof(arrFeignDeath) / sizeof(arrFeignDeath[0]));
							}	
							if (statCoords.back() == array<int,2>({4,1}) && coatable && statFlags.back() != 10) {
								statFlags.push_back(10);
								cout << "Stat flag created! (SF#10)\n";
							}
							if (statCat == 2 && !whenActive && wepType != "Battle Banner" && wepType != "Lunchbox" && statFlags.back() != 11) {
								statFlags.push_back(11);
								cout << "Stat flag created! (SF#11)";
									/*cout << "\nPress ENTER to continue\n";
									cin.ignore()*/
							}
							if (statCoords.back() == array<int,2>({5,26})) {
								statFlags.push_back(12);
								cout << "Stat flag created! (SF#12)\n";
							}
							if (statCoords.back() == array<int,2>({5,35})) {
								statFlags.push_back(15);
								cout << "Stat flag created! (SF#15)\n";
							} 
							if (statCoords.back() == array<int,2>({0,8}) && wepSlot != "melee" && !wearable) {
								clipless = true;
								
							}
							if (statCat == 8 && (subStat == 4 || subStat == 5)) {
								num += meterStatBoostNum;
								meterStatBoostNum++; //offset the reduction later
								/*cout << "Press ENTER to continue\n";
								cin.ignore();*/
							}
						} else {
							downsideNum++;
						}
						if (wepStats.back().statString.find("crit") != string::npos && wepStats.back().statString.find("mmune") == string::npos) {
							critGimmick = true;
							int arr[3][2] = {
								{1,0},
								{1,1},
								{1,2}
							};
							addList(arr, sizeof(arr) / sizeof(arr[0]));
						}
						if (statCat == 2 && (subStat == 0 || subStat == 1)) {
							if (wepType == "Shield" && tfClass == "Demoman" && mod > 0) {
								swap(wepStats.front(), wepStats.back());
								swap(statCoords.front(), statCoords.back());
								wepStats.erase(wepStats.end());
								statCoords.erase(statCoords.end());
							} else {
								tempInt = 1 - subStat; //if ss = 0, ti = 1, if ss = 1, ti = 0
								statsUsed[2][tempInt] = 2;
								cout << "statsUsed[2][" << tempInt << "] = 2\n";
							}
						} 
						if (statCoords.back() == array<int,2>({3,4})) {
							int arr[1][2] = {{3,7}};
							addList(arr, 1);
						} else if (statCoords.back() == array<int,2>({3,7})) {
							int arr[1][2] = {{3,4}};
							addList(arr, 1);
						} 
						if (wepType != "Battle Banner") {
							if (statCat == 3 && (subStat == 1 || subStat == 2)) {
								int arr[1][2] = {{3,3}};
								addList(arr, 1);
							} else if (statCoords.back() == array<int,2>({3,3})) {
								int arr[2][2] = {{3,1}, {3,2}};
								addList(arr, 2);
							}
						}
						if (meterStatBoostNum > 0) {
							meterStatBoostNum--;
						}
						//except for some reason this if else works ???
						if (statPhase == 1) {
							statMade = true; //breaks while loop for first phase
						} else {
							statNum++;
						}
						statAttempts = 0;
					} else {
						cout << "Stat creation failed; retrying...\n";
						//undo changes
						seed.pop_back();
						wepStats.pop_back();
						statCoords.pop_back();
						if (statFlag != -1) {
							statFlags.push_back(statFlag);
							if (statAttempts <= 15) {
								cout << "Stat flag preserved\n";
							} else if (wepStats.back().rating > 0 && statAttempts < 20) {
								cout << "Adding additional upside to try and preserve stat flag\n";
								forceUpside = true;
								forceDur = 1;
							} else {
								cout << "Stat flag removed\n";
								statFlags.pop_back();
								statFlag = -1;
							}
						}
						statAttempts++;
					}
				} else {
					cout << "Stat taken! ({" << statCat << "," << subStat << "}) Seed removed\n";
					statAttempts++;
					seed.pop_back();
					//tempBool = true;
				}
				//temp solution / fallback: (usually means bug)
				if (statAttempts > 125) {
					cout << "Stat creation aborted...Weapon Complete";
					cout << "\nwepRating = " << wepRating << lineBreak("wepRating = " + to_string(wepRating)) << endl;
					return;
				}
			}
		}
		statPhase = 2;
		//filling half stats with 1s
		if (wepType == "Lunchbox") {
			tempInt = 0;
		} else {
			tempInt = 2;
		}
		//most / all statCat 0s
		replace(statsUsed[0].begin(), statsUsed[0].end() - tempInt, 0, 1);
		//non statCat 0s
		//cout << "Adjusting statUsed values for posNegSplit stats: \n";
		for (int i = 0; i < posNegSplitStats.size(); i++) {
			if (statsUsed[posNegSplitStats[i][0]][posNegSplitStats[i][1]] < 1) {
				statsUsed[posNegSplitStats[i][0]][posNegSplitStats[i][1]] = 1;
				//cout << "statsUsed [" << posNegSplitStats[i][0] << "][" << posNegSplitStats[i][1] << "] = 1\n";
			} /*else {
				cout << "  ";
			}
			cout << "statsUsed [" << posNegSplitStats[i][0] << "][" << posNegSplitStats[i][1] << "] = " << statsUsed[posNegSplitStats[i][0]][posNegSplitStats[i][1]] << endl;*/
		}
		//phase 2 blacklist
	}
}
void Wep::printStats(bool debug) {
	//for debug :)
	cout << "WEAPON\n\n";
	cout << "Level " << rand() % 100 << " " << wepType << " (" << tfClass << " " << realWepSlot << ")\n\n";
	if (whenActive) {
		cout << "When weapon is active:\n";
	}
	for (int i = 0; i < wepStats.size(); i++) {
		cout << wepStats[i].statString << endl;
	}
	if (debug) {
		cout << "\nDEBUG INFO\n\nVersion: v." << versionFull << "\nWeapon Rating: " << to_string(wepRating) << "\nstatCoords: ";
		for (int i = 0; i < statCoords.size(); i++) {
			cout << "{" << statCoords[i][0] << ", " << statCoords[i][1] << "}";
			if (i != statCoords.size() - 1) {
				cout << ", ";
			}
		}
		cout << "\nSeed: ";
		if (!preSeed) {
			for (int i = 0; i < seed.size(); i++) {
				if (i != 0) {
					cout << "-";
				}
				cout << seed[i];
			}
		} else {
			cout << "N/A\n";
		}
		if (invisWatchCloakTypeIndex == 2) {
			cout << "\nFeign Duration: " << invisWatchFeignDuration << "s";
		}
		//prolly add more later
	}
	cout << "\n\nEND WEAPON" << lineBreak("END WEAPON");
}