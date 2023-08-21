#include "weapon.hpp"
const array<array<int,2>,20> statsToOutside = {{
	//all (0-8)
	{1,3},
	{1,11},
	{1,15},
	{4,1},
	{4,2},
	{4,7},
	{5,0},
	{5,17},
	{5,26},
	//banner (9-13)
	{1,7},
	{2,1},
	{2,2},
	{3,1},
	{3,2}
}};
const array<array<int,2>,2> statsToTop = {{
	//all (0-1)
	{1,13},
	{1,14},
}};
const array<array<int,2>,25> posNegSplitStats = {{ //besides statCat 0
	{1,16},
	{4,1},
	{4,2},
	{4,7},
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
	{8,4},
	{8,7}
}};
const array<array<int,2>,13> dynamicStats = {{
//$d [0]
	{2,1}, //0
//$h [1]
	{3,5}, //1
//$j [2]
	{3,6}, //2
//$o [3-7]
	{1,13}, //3
	{1,14}, //4 (on kill)
	{4,2}, //5
	{5,28}, //6
	{5,34}, //7 (on kill)
//$s [8-10]
	{1,10}, //8
	{1,12}, //9
	{5,18}, //10
	{8,0}, //11
	{8,4} //12
}};
//the old method of determining the type of dStat was stupid. I've changed it to where there is a variable in the stat itself that assigns to the index of the type of dStat in the UDSE array, and is set to -1 if there is no changes to UDSE (meaning its not a dynamic stat).
array<array<int,2>,7> dynamicNum = {{ //2 values, first value is for the max possible values for each type, the second is for the index of the first stat in the dynamicStats array corrisponding to each wordflag type. The wordflag's index is in the same order as in the usedDynamicStatEntries array, and due to this, index 0 is a placeholder. Index 6 is used to mark the end of the coordinate list (otherwise index 5 wouldn't work properly)
	{1,0}, //single-value flags, 0
	{damTypes.size() - 1, 0}, //$d, 1 (minus self-damage for explosives)
	{HPContainerTypes.size(), 1}, //$h, 2
	{ammoContainerTypes.size(), 2}, //$o, 3
	{rewards.size(), 3}, //$j, 4
	{statTypes.size(), 8}, //$s, 5 
	{0, dynamicStats.size()} //no stat flag, marks the end of the list, 6
}};
int Wep::addSeed(int digits) {
	if (digits < 1) {
		digits = 3;
	}
	int newSeed = time(NULL) * (seedSegLengths.size() + 1);
	//idk why I have to use a tempInt compiler is being cringe
	tempInt = pow(10, digits);
	newSeed %= tempInt;
	newSeed = abs(newSeed);
	while (to_string(newSeed).length() < digits) {
		//cout << "wls.";
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
	seedAdded = true;
	seedCalls = 1; //double check for correct val
	cout << "Added seed: " << newSeed << endl;
	return newSeed;
}
/*int Wep::reSeedRand(int digits) {
	seedAdded = false;
	switch ((seedCalls) % 10) {
		case 0:
			return addSeed(digits);
		case 5:
			srand(-1 * seed.back());
			return -1 * seed.back();
		default:
			if ((seed.size() - 1) % 8 < 4) {
				return seed.back();	
			} else {
				return -1 * seed.back();
			}
	}
};*/
void Wep::addList(int arr[][2], int size, bool whitelist) {
	cout << endl;
	if (whitelist) {
		tempInt = 0; //whitelist doesn't work like an actual whitelist, it just un-blacklists stats instead of exclusively offering some stats. Real whitelist would be inefficent most of the time.
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
					{1,16}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else {};
			break;
		case 1:
			//weapon
			if (wepType == "Cleaver") { 
				int arrWL[9][2] = {
					{0,3},
					{0,11},
					{1,0},
					{1,1},
					{1,2},
					{1,3},
					{1,11},
					{1,13},
					{1,14}
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
			} else if (wepType == "Wrench" || wepType == "Robot Arm") {
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
				int arrWL[10][2] = {
					{0,3},
					{1,0},
					{1,1},
					{1,8},
					{5,23},
					{8,6},
					{5,40},
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
			} else if (wepType == "Bow") {
				int arr[1][2] = {
					{1,8}
				};
				addList(arr, sizeof(arr) / sizeof(arr[0]));
			} else if (wepType == "Sapper") {
				whenActive = true;
				int arrBL[5][2] = {
					{0,-1},
					{1,-1},
					{2,-1},
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
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
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
				int arrWL[1][2] = {
					{1,8}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (tfClass == "Spy") {
        int arrBL[1][2] = {
					{0,10}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
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
			if (whenActive && wepType != "Battle Banner" && wepType != "Lunchbox") {	
				int arr[2][2] = {
					{1,7},
					{2,2}
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
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[4][2] = {
					{1,7},
					{1,10},
					{1,12},
					{5,17}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
			} else if (hasMeter) {
				int arrBL[1][2] = {
					{1,16}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
				int arrWL[1][2] = {
					{5,13}
				};
				addList(arrWL, sizeof(arrWL) / sizeof(arrWL[0]), true);
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
					{0,1},
					{1,4},
					{1,8}
				};
				addList(arrBL, sizeof(arrBL) / sizeof(arrBL[0]));
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
			} else {
				cout << "N/A";
			}
			cout << endl;
			break;
		default:
			cout << "\nuh oh\n\n";
	}
};
Wep::Wep(int num, int preDefWepType, int preDefWepSlot, int preDefClass, int modMax, int modSplitPoint, int statNumMax, vector<array<int,3>> preDefStatData, bool exactUpside, bool exactDownside, int preDefProperties[2], bool debug, bool bypassRating, bool bypassBlacklist, bool anyWepAnyClass, bool lockedModValue) {
	//var assignment & handling params
	for (int i = 0; i < distance(usedDynamicStatEntries.begin(), usedDynamicStatEntries.end()); i++) {
		//cout << "i = " << i << endl;
		if (i == 0) {
			usedDynamicStatEntries[0].assign(6,-1);
			//cout << "usedDynamicStatEntries[0].size() = " << usedDynamicStatEntries[0].size() << endl;
		} else {
			usedDynamicStatEntries[i].clear();	
			//cout << "usedDynamicStatEntries[" << i << "].size() = " << usedDynamicStatEntries[i].size() << endl;
		}
	}
	//cout << "Press ENTER to continue\n";
	//cin.ignore();
	statFlagPass = false;
	bannerBuffTypeIndex = -1;
	invisWatchCloakTypeIndex = -1;
	invisWatchFeignDuration = -1;
	tfClass = "Multi";
	ammoType = "bullet";
	statFlag = -1;
	tempInt = 0;
	if (modMax < 2) {
		modMax = 20;
	}
	if (num < 1) {
		num = 2;
	} 
	//reset dynamicNums. I could just make this a local variable within the class, but... I dont want to fuck with anything rn i feel like ass
	dynamicNum[1][1] = damTypes.size() - 1;
	dynamicNum[2][1] = HPContainerTypes.size();
	dynamicNum[3][1] = ammoContainerTypes.size();
	dynamicNum[4][1] = rewards.size();
	dynamicNum[5][1] = statTypes.size();
	if (statNumMax >= 0 && statNumMax <= num) {
		noDownsides = true;
	} else {
		noDownsides = false;
		if (statNumMax < 0) {
			statNumMax = int(round(num * 2.5));
			cout << "num = " << num << "; num * 2.5 = " << to_string(num * 2.5) << "; statNumMax = " << statNumMax << endl;
		}
	}
	for (int i = 0; i < 2; i++) {
		if (abs(preDefProperties[i]) > 1) {
			preDefProperties[i] = -1;
		}
	}
	cout << "num = " << num << "; preDefWepType = " << preDefWepType << "; preDefWepSlot = " << preDefWepSlot << "; preDefClass = " << preDefClass << "; modMax = " << modMax << "; modSplitPoint = " << modSplitPoint << "; statNumMax = " << statNumMax << "; exactUpside = " << exactUpside << "; exactDownside = " << exactDownside << "; whenActive = " << preDefProperties[0] << "; hasMeter = " << preDefProperties[1] << "; debug = " << debug << "; bypassRating = " << bypassRating << ";  bypassBlacklist = " << bypassBlacklist << "; anyWepAnyClass = " << anyWepAnyClass << "; lockedModValue = " << lockedModValue << "; noDownsides = " << noDownsides << endl;
	//statCoords constructer for predefined stats
	preDefStatData.push_back(array<int,3>({-1,-1,-1}));
	while (preDefStatData[tempInt][0] != -1 && !preDefStatData.empty()) {
		//cout << "wlsc.";
		statCoords.push_back(array<int, 2> ({preDefStatData[tempInt][0], preDefStatData[tempInt][1]})); //copies preDefStatData's coordinates to statCoords
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
				if (i < 4 || bypassBlacklist) {
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
	if (preDefWepType < 0 || preDefWepType >= weaponList.size()) {
		if (preDefWepSlot >= 0 && preDefWepSlot < weaponSlots.size()) {
			switch(preDefWepSlot) {
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
			tfClass = "Spy";
			wepType = "Invis Watch";
			cout << "!!!!!";
		}
		cout << wepSlot << endl;
		if (preDefClass > 0 && preDefClass <= classList.size()) {
			classIndex = preDefClass;
			tfClass = classList[classIndex];
			cout << tfClass << endl;
		} else {
			if (wepSlot != "PDA1") {
				tempInt = wepIndexCeiling - wepIndexFloor;
				wepIndex = rand() % tempInt + wepIndexFloor;
				wepType = weaponList[wepIndex];	
			}
		}
	} 
	if (wepType == "") {
		if (preDefWepType > 0 && preDefWepType <= weaponList.size()) {
			wepType = weaponList[preDefWepType];
			wepIndex = preDefWepType;
		} else {
			while (true) {
				cout << ".";
				wepType = classWeapons[classIndex][rand() % classWeapons[classIndex].size()];
				wepIndex = distance(weaponList.begin(), find(weaponList.begin(), weaponList.end(), wepType));
				if ((wepIndex >= wepIndexFloor && wepIndex < wepIndexCeiling) || (wepSlot == "" || wepIndexFloor + wepIndexCeiling == 0)) {
					break;
				}
			}
		}
		if (wepSlot == "") {
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
	}
	realWepSlot = wepSlot;
	cout << "This weapon is a " << realWepSlot << " weapon!\n";
	cout << "This weapon is a " << wepType << "!\n";
	if (tfClass == "Multi" && wepType != "") {
		for (int i = 0; i < classWeapons.size(); i++) {
			/*cant use find() in multidimesional array so... take the array to a vector lol I have no idea if this works :) 
	ANYWAYS this determens the class based on the weapon
	old code:
	tempInt = distance(begin(classWeapons), find(begin(classWeapons[classIndex]), end(classWeapons[classIndex]), weaponList[tempInt]));
			if (find(tempVector.begin(), tempVector.end(), weaponList[tempInt]) != tempVector.end()) {
				break;
			}
			*/ 
			vector<string> tempVector(classWeapons[i].begin(), classWeapons[i].end()); 
			if (find(tempVector.begin(), tempVector.end(), wepType) != tempVector.end()) {
				classIndex = i;
				tfClass = classList[i];
				break;
			}
		}
	}
	cout << "This weapon is for the " << tfClass << "!\n";
	
	//for weapons that are used more as a primary / secondary 
	if (find(primaryLike.begin(), primaryLike.end(), wepType) != primaryLike.end()) {
			cout << "This weapon is like a primary!\n";
			wepSlot = "primary";
		} 
		if (find(secondaryLike.begin(), secondaryLike.end(), wepType) != secondaryLike.end()) {
			cout << "This weapon is like a secondary!\n";
			wepSlot = "secondary";
		}
  tempInt = rand() % 100;
	cout << "tempInt = " << tempInt << endl;
	//whenActive (decides if stats are passive or active)
  if (preDefProperties[0] == 1 || (preDefProperties[0] && (wepSlot == "primary" && tempInt < 15) || (wepSlot == "secondary" && tempInt < 50) || (wepSlot == "melee" && tempInt < 85))) {
		whenActive = true;
	} else {
		whenActive = false;
	}
	tempInt = distance(meterWeapons.begin(), find(meterWeapons.begin(), meterWeapons.end(), wepType));
	if (tempInt != distance(meterWeapons.begin(), meterWeapons.end())) {
		hasMeter = true;
		meterIndex = tempInt;
		meterName = meterNames[tempInt];
	}
	//clipless (if weapons dont have a clip, e.g. Minigun, Flare Gun, Sniper Rifle)
	if (find(cliplessWeapons.begin(), cliplessWeapons.end(), wepType) != cliplessWeapons.end()) {
		cout << "This weapon has no clip!\n";
		clipless = true;
	}	
	//weapons that just kinda suck ass
	tempInt = distance(alreadyBad.begin(), find(alreadyBad.begin(), alreadyBad.end(), wepType));
	if (tempInt != distance(begin(alreadyBad), end(alreadyBad))) {
		cout << "Bad weapon! (lol)\n";
		wepRating -= howBad[tempInt];
	}
	//removes * on "Boots*", "Parachute*", & the shotguns. All weapon checks past this point will not put class into account
	while (wepType.find('*') != string::npos) {
		//cout << "wl*.";
		wepType.erase(wepType.find('*'), 1);
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
			wepRating -= 5;
		} else if (wepType == "Shield" && tfClass == "Sniper") {
			wepRating += 26;
		}
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
			wepRating -= 20;
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
	//dynamicNum correction
	if (wearable) {
		dynamicNum[5][0] = 3; //3 wearable stats
	}
	if (projectile) {
		dynamicNum[5][0]++; //1 projectile-exclusive stat
	}
	if (explosive) {
		dynamicNum[1][0] += 1; //self-damage stat
		dynamicNum[5][0] += 2; //2 explosive-exclusive stat
	}
	if (bypassBlacklist) {
		cout << "Blacklist Skipped!" << lineBreak("Blacklist Skipped!");
	} else {
		blacklist(0);
		blacklist(3);
		blacklist(1);
		blacklist(2);
		cout << lineBreak("statsUsed[n][n] = n", false, true);
	}
	//statCalculation
	statPhase = 1;
	//n loop is for downsides
	for (int n = 0; n < 2; n++) {
		cout << "statPhase = " << to_string(statPhase);
		if (num < 1) {
			num = 1;
		}
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
				seedAdded = false;
				//cout << "wlsm.";
				cout << endl;
				//determines if stats should be calculated, true means do
				if (statCoords.size() <= statNum) {
					randomStat = true;		
				}
				if (randomStat || tempBool) {
					tempBool = false; //???
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
					subStat = rand() % statCatNum[statCat];
					tempInt = rand() % 100;	
				} else {}
				if (statFlags.empty()) {
					statFlags.push_back(-1);
				}
				cout << "statCat = " << statCat << "; subStat = " << subStat << "; mod = " << mod << "; statFlags.back() = " << statFlags.back() << endl; //here is temp
				if (statFlags.back() > -1) {
					cout << "\n\nOhSheeetARat\n\n\n";
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
							case 5: //tickle mittens pt.2
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
							case 9:
								statCat = 8;
								subStat = 7;
								statFlagPass = true;
								break;
							case 10:
								statCat = 1;
								subStat = 16;
								break;
							case 11:
								statCat = 2;
								subStat %= statCatNum[2] + 1;
								break;
							case 13:
								statCat = 1;
								subStat = 11;
								break;
							case 14:
								statCat = 8;
								subStat = 4;
								statFlagPass = true;
								break;
							case 15:
								statCat = 5;
								subStat = 0;
								break;
						} //statFlag redirection	
					} else if (mod > 0 && statFlag % 4 == 0) {
						cout << "Stat flag detected! (SF#" << statFlag << ")\n";
						randomStat = true; //so statcoords are added regardless
						statFlags.pop_back();
						switch(statFlag) {
							case 0:
								statCat = 1;
								subStat = 6;
								break;
							case 4:
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
						case 8:
							statCat = 5;
							subStat = 20;
							break;
						case 12:
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
					} else if (!(wearable || throwable || wepType == "Medigun" || !preDefProperties[1]) && (preDefProperties[1] == 1 || (realWepSlot == "primary" && tempInt < 6) || (realWepSlot == "secondary" && tempInt < 4) || (wepSlot == "melee" && tempInt < 2))) {
						/*if (tempInt % 2 != 0) {*/
							cout << "!METER!... tfClass = " << tfClass << "; classIndex = " << classIndex << "; classMeterNames[" << classIndex << "].size() = " << classMeterNames[classIndex].size() << endl;
							hasMeter = true;
							vector<string> tempVector(classMeterNames[classIndex].begin(), classMeterNames[classIndex].end());
							while (tempVector.back() == "") {
								//cout << "wlm.";
								tempVector.pop_back();
							}
							meterName = tempVector[rand() % tempVector.size()];
							if (meterName == "") {
								meterName = "charge";
							}
							statCat = 8;
							subStat = 4;
							int arr[2][2] = {
								{5,13},
								{8,4}
							};
							addList(arr, sizeof(arr) / sizeof(arr[0]), true);
							if (wepType != "primary") {
								if (!whenActive && rand() % 5 == 0) {
									whenActive = true;
								} else {
									whenActive = false;
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
				//also temp
				cout << ".,.";
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
					dynamicStat = false;
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
					//wow much better why didnt i think of this before fuck
					if (wepStats[statNum].dStatType > 0) {
						dynamicStat = true;
						cout << "Dynamic stat!\n";
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
									} else */if (wepType != "Battle Banner" && !coatable) {
										break;
									}
								}
								cout << "j = " << j << "\nDoes {" << wepStats[i].coords[0] << "," << wepStats[i].coords[1] << "} = {" << statsToOutside[j][0] << "," << statsToOutside[j][1] << "} or {0,n}? ";
								if (wepStats[i].coords[0] == 0 || wepStats[i].coords == statsToOutside[j] || (wepType == "Battle Banner" || wepType == "Medigun") && wepStats[i].statString.find("max") != string::npos) {
									cout << "Yes, moving stat to outisde of weapon stats\n";
									//temp
									if (hasMeter) {
										cout << "METER STAT IS MOVING WEE WOO WEE WOO\nFirst stat in list: " + wepStats.front().statString; 
									}
									if (wepStats[i].realUpside) {
										if (coatable || isSword || (hasMeter && wepStats.front().statString.find("Build") != string::npos)) {
											tempInt = 1;
										} else {
											tempInt = 0;
										}
										if (wepType == "Battle Banner" && (statCat == 0 || (statCat == 1 && (subStat == 13 || subStat == 14)))) {
											cout << "!!!!!!!!!\n";
											for (int j = 0; j < wepStats.size(); j++) {
												if (wepStats[j].statString.find("Provides") != string::npos) {
													tempInt = j;
													break;
												} else {tempInt = 0;}
											}
										} else {tempInt = 0;}
										if (wepType == "Battle Banner" || wepType == "Medigun") {
											cout << "tempInt = " << tempInt << endl;
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
									cout << "No.\n";
								}
							}
						}
						statNum = (int) wepStats.size() - 1;
						cout << "\nWeapon Complete\n" << lineBreak("Weapon Complete") << endl;
						return; //weapon is balanced; end stat creation
					} else if (wepStats.back().statString != "" && abs(newWepRating) < 500 &&
					((!noDownsides && 
					(statPhase == 1 || newWepRating >= -2.5 || wepRating < -2.5) && statNum < statNumMax)
					//banner conditions
					|| (noDownsides && newWepRating < 2.5))) {
						if (!dynamicStat) {
							if (posNegSplit) {
								statsUsed[statCat][subStat] += 1;
							} else {
								statsUsed[statCat][subStat] += 2;	
							}	
						} else {
							/*I forgot how this works orz... I think i is used for the index of usedDynamicStatEntries and j is used for index of dynamicNum or visa versa? or they're both used for the same thing but at different indexes? 
							Update... I got rid of j... I dont think we need J at all*/
							//int j = 1; 
							for (int i = 1; i < usedDynamicStatEntries.size(); i++) {
								//cout << "i = " << i /*<< "; j = " << j*/ << endl;
								if (usedDynamicStatEntries[i].size() == dynamicNum[i][0]) {
									cout << "used all possible values for dynamicStat " << i << endl;
									for (int j = dynamicNum[i][1]; j < dynamicNum[i+1][1]; j++) { // good enough
										statsUsed[dynamicStats[j][0]][dynamicStats[j][1]] += 2;
										if (statPhase == 1) {
											for (int k = 0; k < posNegSplitStats.size(); k++) {
												if (dynamicStats[j] == posNegSplitStats[k]) {
													statsUsed[dynamicStats[j][0]][dynamicStats[j][1]] = 1;
												}
											}
										}
										cout << "statsUsed[" << dynamicStats[j][0] << "][" << dynamicStats[j][1] << "] = " << statsUsed[dynamicStats[j][0]][dynamicStats[j][1]] << endl;
									}
									cout << "dynamicNum[" << i << "][1] = " << dynamicNum[i][1] << "; dynamicNum[" << i+1 << "][1] = " << dynamicNum[i+1][1] << "; Press ENTER to continue: \n";
									cin.ignore();
								}
							}
							//manual checks
							if (count_if(usedDynamicStatEntries[4].begin(), usedDynamicStatEntries[4].end(), [](int i){return i < 8;}) == dynamicNum[4][1] / 2) {
							}
						}
						cout << "Stat creation successful!\n";
						/*cout << "Press ENTER to continue\n";
						cin.ignore();
						cout << "statsUsed[" << statCat << "][" << subStat << "] = " << statsUsed[statCat][subStat] << endl;
						cout << "wepStats.size() = " << wepStats.size() << "; statNum = " << statNum << endl;*/
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nwepRating = " << wepRating << endl;
						if (forceDur >= 0) {
							forceDur--;
							if (forceDur <= 0) {
								forceDur = -1;
								forceUpside = false;
								forceDownside = false;
							}
						}
						//stat flag creation, dynamic stat tweaks, & other stat specific stuff 
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
								if (statNum + 1 == num) {
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
									statFlags.push_back(10);
									cout << "Stat flag created! (SF#10)\n";
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
								statFlags.push_back(8);
								cout << "Stat flag created! (SF#8)\n";
								if (statNum + 1 == num) {
									num++;
								}
							}
							if (statCat == 2 && !whenActive && !wearable && !(wepType == "Lunchbox" || wepType == "Medigun" || wepType == "Battle Banner") && statFlags.back() != 11) {
								statFlags.push_back(11);
								cout << "Stat flag created! (SF#11)";
									/*cout << "\nPress ENTER to continue\n";
									cin.ignore()*/
							}
							if (statCoords.back() == array<int,2>({5,35})) {
								statFlags.push_back(12);
								cout << "Stat flag created! (SF#12)\n";
								if (statNum + 1 == num) {
									num++;
								}
							} 
							if (statCoords.back() == array<int,2>({5,26})) {
								statFlags.push_back(13);
								cout << "Stat flag created! (SF#13)\n";
							}
							if (statCoords.back() == array<int,2>({0,8}) && wepSlot != "melee" && !wearable) {
								clipless = true;
								
							}
							if (statCoords.back() == array<int,2>({8,4}) && wepStats.back().statString.find("increases with") != string::npos) {
								statFlags.push_back(14);
								cout << "Stat flag created! (SF#14)\n";
							}
							if (statCat == 8 && (subStat == 4 || subStat == 5)) {
								if (meterStatBoostNum > 0) {							
									num += meterStatBoostNum;
									meterStatBoostNum++; 	
								} else if (meterStatBoostNum == -2) {
									num = 1;
								}
								//offset the reduction later
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
						//if udse[1] has 4 or 5, add 0, 1, & 2, but if it has 0, 1, or 2, add 4 & 5 (while making sure no duplicates) 
						bool rangDType = false;
						bool melDType = false;
						if (find(usedDynamicStatEntries[1].begin(), usedDynamicStatEntries[1].end(), 4) != usedDynamicStatEntries[1].end()) {
							rangDType = true;
						} else if (find(usedDynamicStatEntries[1].begin(), usedDynamicStatEntries[1].end(), 5) != usedDynamicStatEntries[1].end()) {
							melDType = true;
						}
						if (find(usedDynamicStatEntries[1].begin(), usedDynamicStatEntries[1].end(), 0) != usedDynamicStatEntries[1].end()) {
							if (!rangDType && !melDType) {
								usedDynamicStatEntries[1].push_back(4);
								usedDynamicStatEntries[1].push_back(5);
							}
						} else if(rangDType || melDType) {
							usedDynamicStatEntries[1].push_back(0);
						}
						if (find(usedDynamicStatEntries[1].begin(), usedDynamicStatEntries[1].end(), 1) != usedDynamicStatEntries[1].end()) {
							if (!rangDType && !melDType) {
								usedDynamicStatEntries[1].push_back(4);
								usedDynamicStatEntries[1].push_back(5);
							}
						} else if(rangDType || melDType) {
							usedDynamicStatEntries[1].push_back(1);
						}
						if (find(usedDynamicStatEntries[1].begin(), usedDynamicStatEntries[1].end(), 2) != usedDynamicStatEntries[1].end()) {
							if (!rangDType && !melDType) {
								usedDynamicStatEntries[1].push_back(4);
								usedDynamicStatEntries[1].push_back(5);
							}
						} else if(rangDType || melDType) {
							usedDynamicStatEntries[1].push_back(2);
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
						if (!seed.empty() && seedAdded) {
							int removedVal = seed.back();
							seed.pop_back();	
							cout << "Seed (" << removedVal << ") removed; ";
						} else {
							cout << "ERROR: seed not removed (vector empty)";
						}if (!wepStats.empty() && !statCoords.empty()) {
							string removedStr = wepStats.back().statString;
							if (removedStr.length() > 25) {
								removedStr = removedStr.substr(0,22) + "...";
							}
							wepStats.pop_back();	
							statCoords.pop_back();
							cout << "Stat \"" << removedStr << "\" removed; ";
						} else {
							cout << "ERROR: stat not removed (vector empty)";
						}
						if (statFlag != -1) {
							statFlags.push_back(statFlag);
							if (statAttempts <= 15) {
								cout << "Stat flag (SF# " << statFlag << ") preserved";
							} else if (wepStats.back().rating > 0 && statAttempts < 20) {
								cout << "Adding additional upside to try and preserve stat flag (SF# " << statFlag << ")";
								forceUpside = true;
								forceDur = 1;
							} else {
								cout << "Stat flag (SF# " << statFlag << ") removed";
								statFlags.pop_back();
								statFlag = -1;
							}
							cout << ";";
						}
						if (dynamicStat) { //see if added dynamic stat values 
							bool dStatCheck = false; 
							int dStatInd = wepStats[statNum].dStatType;
							//again cant use find on multidimensonal arrays... fun
							//for (int i = 0; i < dynamicStats.size(); i++) { 
								//cout << "i = " << i;
								//if (array<int,2>({dynamicStats[i][0], dynamicStats[i][1]}) == array<int,2>({statCat, subStat})) {
									//dStatCheck = false;
									//cout << "; ";
									//for (int j = 0; j + 1 < dynamicNum.size(); j++) {
										//cout << "j = " << j << endl;
										//if (i < dynamicNum[j+1][1] || usedDynamicStatEntries[j].back() < 0) {
							if (dStatInd > 0) {
								if (!usedDynamicStatEntries[dStatInd].empty()) {
									int removedVal = usedDynamicStatEntries[dStatInd].back();
									usedDynamicStatEntries[dStatInd].pop_back();
									cout << "dynamicStat #" << dStatInd << " value (" << removedVal << ") removed";
								} else {
									cout << "ERROR: dynamicStat value not removed (vector empty; UDSE[" << dStatInd << "].size() = " << usedDynamicStatEntries[dStatInd].size() << ")... Press ENTER to continue";
									cin.ignore();
								}
								dStatCheck = true;
							} else {
								cout << "ERROR: dynamicStat #" << dStatInd << " value (" << usedDynamicStatEntries[dStatInd].back() << ") not removed... Press ENTER to continue";
								cin.ignore();
								dStatCheck = true;
							}
										//break;
										//}
									//}
								//} else {
									//cout << endl;
								//}
							//}
							if (!dStatCheck) {
								cout << "ERROR: dynamicStat #" << dStatInd << " value (" << usedDynamicStatEntries[dStatInd].back() << ") not removed (!dStatCheck)... Press ENTER to continue";
								cin.ignore();
								dStatCheck = true;
							}
						}
						cout << endl;
						statAttempts++;
					}
				} else {
					cout << "Stat taken! ({" << statCat << "," << subStat << "}); ";
					statAttempts++;
					if (!seed.empty()) {
						int removedVal = seed.back();
						seed.pop_back();	
						cout << "Seed (" << removedVal << ") removed";
					} else {
						cout << "ERROR: seed not removed (vector empty)";
					}
					if (statFlag > -1) {
						cout << "; Stat flag (SF# " << statFlag << ")";
						if (statFlag == 11 && statAttempts < 50) {
							statFlags.push_back(statFlag);
							cout << "preserved";
						} else {
							cout << "removed";
						}
						cout << ";";
						statFlag = -1;
					}
					cout << endl;
					//tempBool = true;
				}
				//temp solution / fallback: (usually means bug)
				if (statAttempts % 250 == 0 && statAttempts > 249) {
					cout << "statAttempts = " << statAttempts << "\nPress ENTER to continue\n";
					cin.ignore();
				}
				if (statAttempts > 750) {
					cout << "Stat creation aborted...Weapon Complete";
					cout << "\nwepRating = " << wepRating << lineBreak("wepRating = " + to_string(wepRating)) << endl;
					return;
				}
			}
		}
		statPhase = 2; //phase 2 initialization
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
		//phase 2 dynamicNum modifiers
		dynamicNum[4][0] = usedDynamicStatEntries[4].size() + penalties.size(); //makes the max val number equal to the number of values currently used, making dStat 4 'filled' (which is what we want since no more positive values can be added), and adds space for the values for penalties 
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
			if (i + 1 != statCoords.size()) {
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
		//cout << "\nUDSE size: " << usedDynamicStatEntries.size() << endl;
		cout << "\nDynamic Stat Array:  ";
		//resetting changed dynamicNum vals (only those changed for phase 2, not changed per weapon), only to report the true max value for debugging
		dynamicNum[4][0] = rewards.size() + penalties.size();
		for (int i = 0; i < usedDynamicStatEntries.size(); i++) {
			//cout << "\ni = " << i;
			cout << endl << dynamicStatFlagNames[i] << ": ";
			if (!usedDynamicStatEntries[i].empty()) {
				//cout << "\nUSDE[" << i << "].size(): " << usedDynamicStatEntries[i].size() << "; (int) USDE[" << i << "].size(): " << (int) usedDynamicStatEntries[i].size() << ",";	
				//vector.size() overflow check
				if ((int) usedDynamicStatEntries[i].size() < 0) {
					cout << "ERROR: vector.size() underflow, attempting to recover\n";
					usedDynamicStatEntries[i].push_back(0);
					usedDynamicStatEntries[i].pop_back();
					cout << "(post-adj): (int) USDE[" << i << "].size(): " << (int) usedDynamicStatEntries[i].size() << endl;	
					if ((int) usedDynamicStatEntries[i].size() < 0) {
						cout << "ERROR: unrecoverable vector.size() underflow, aborting...press ENTER to continue\n";
						cin.ignore();
						break;
					}
				}
				//cin.ignore();
				for (int j = 0; j < usedDynamicStatEntries[i].size(); j++) {
					//cout << "\nj = " << j << endl;
					//cin.ignore();
					if (i == 0) {
						cout << singValStatFlagNames[j] << ": ";
					} else {
						//cout << "..,";
						//cin.ignore();
						sort(usedDynamicStatEntries[i].begin(), usedDynamicStatEntries[i].end());
					}
					//cout << "\nUSDE[" << i << "][" << j << "]: " << usedDynamicStatEntries[i][j] << ",";
					//cin.ignore();
					tempInt = usedDynamicStatEntries[i][j];
					tempString = "-";
					//cout << "...,";
					//cin.ignore();
					if (tempInt > -1) {
						tempString = to_string(tempInt); 	
					}
					if (j + 1 < usedDynamicStatEntries[i].size()) {
						tempString += ", ";
					} 
					cout << tempString;
				}
				if (i != 0) {
					cout << " (Used ";
					if (usedDynamicStatEntries[i].size() == dynamicNum[i][0]) {
						cout << "all";
					} else {
						cout << usedDynamicStatEntries[i].size() << " out of " << dynamicNum[i][0];
					}
					cout << " possible values)";
				}
			} else {
				cout << "-";
			}
		}
		//prolly add more later
	}
	cout << "\n\nEND WEAPON" << lineBreak("END WEAPON");
}